/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:28:21 by olmohame          #+#    #+#             */
/*   Updated: 2024/08/01 05:13:35 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_token(char **str, int expand, t_sub *sub, t_shell *shell)
{
	char	*new_token;
	t_param	param;

	init_expansion_param(&param);
	new_token = ft_strdup(*str);
	if (!new_token)
		exit(exit_msg(&shell, "Malloc failed.\n", 0, EXIT_FAILURE));
	while ((*str)[++(param.i)])
	{
		if (expand && \
			((*str)[param.i] == '$' && is_expandable(*str, param.i)))
		{
			expand_var(str, &param, &new_token, shell);
			continue ;
		}
		new_token[++(param.start_index)] = (*str)[(param.i)];
	}
	new_token[++(param.start_index)] = 0;
	free(*str);
	*str = NULL;
	*str = new_token;
	sub->invalid_expansion = param.status == 0;
	return (param.status == 0);
}

static void	clean_quotes(char **str, t_param *param, char **new_token)
{
	if (in((*str)[param->i], "\'\""))
	{
		if (param->out_quo == '*')
			param->out_quo = (*str)[param->i];
		else if ((*str)[param->i] == param->out_quo)
			param->out_quo = '*';
		else
			(*new_token)[++(param->start_index)] = (*str)[param->i];
	}
	else
		(*new_token)[++(param->start_index)] = (*str)[(param->i)];
}

int	clean_token(char **str, t_shell *shell)
{
	char	*new_token;
	t_param	param;

	if (!str || !(*str))
		return (1);
	init_expansion_param(&param);
	new_token = ft_strdup(*str);
	if (!new_token)
		exit(exit_msg(&shell, "Malloc failed.\n", 0, EXIT_FAILURE));
	while ((*str)[++(param.i)])
		clean_quotes(str, &param, &new_token);
	new_token[++(param.start_index)] = 0;
	free(*str);
	*str = NULL;
	*str = new_token;
	return (param.status == 0);
}

static void	clean_list(t_shell *shell, t_sub **sub)
{
	int		resplit;
	ssize_t	i;
	ssize_t	old_i;
	ssize_t	num_tokens;

	num_tokens = count_elements((*sub)->cmd_arr);
	i = -1;
	while ((*sub)->cmd_arr[++i])
	{
		resplit = has_expandable_variable((*sub)->cmd_arr[i]);
		expand_token((*sub)->cmd_arr + i, 1, (*sub), shell);
		if ((*sub)->invalid_expansion && !ft_strlen((*sub)->cmd_arr[i]))
		{
			free((*sub)->cmd_arr[i]);
			(*sub)->cmd_arr[i] = NULL;
		}
		old_i = i;
		if (resplit && (*sub)->cmd_arr[i])
			rebuild_cmd(shell, sub, &num_tokens, &i);
		clean_sequence(shell, sub, old_i, i);
	}
	order_list(sub, num_tokens);
}

void	creat_cmd_list(t_sub **lst, t_shell *shell)
{
	t_sub	*temp;

	if (lst && *lst)
	{
		temp = *lst;
		temp->cmd_arr = sh_split(temp->str);
		if (!temp->cmd_arr)
			exit(exit_msg(&shell, "Malloc failed.\n", 0, EXIT_FAILURE));
		clean_list(shell, &temp);
		while (temp->next != *lst)
		{
			temp = temp->next;
			temp->cmd_arr = sh_split(temp->str);
			if (!temp->cmd_arr)
				exit(exit_msg(&shell, "Malloc failed.\n", 0, EXIT_FAILURE));
			clean_list(shell, &temp);
		}
	}
}
