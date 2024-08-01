/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utills.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 03:22:22 by olmohame          #+#    #+#             */
/*   Updated: 2024/07/25 09:58:38 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quoted(char *str, long ind)
{
	long	i;
	char	out_quo;

	i = -1;
	out_quo = '*';
	while (str[++i])
	{
		if (in(str[i], "\'\""))
		{
			if (out_quo == '*')
				out_quo = str[i];
			else if (str[i] == out_quo)
				out_quo = '*';
		}
		if (i == ind)
			break ;
	}
	return (out_quo != '*');
}

static void	init_param(t_param *param, char *str)
{
	param->i = -1;
	param->out_quo = '*';
	param->accept = str[0] != '\'';
}

int	is_expandable(char *str, long ind)
{
	t_param	param;

	init_param(&param, str);
	while (str[++(param.i)])
	{
		if (in(str[param.i], "\'\""))
		{
			if (param.out_quo == '*')
			{
				param.out_quo = str[param.i];
				param.accept = str[param.i] == '"';
			}
			else if (str[param.i] == param.out_quo)
			{
				param.out_quo = '*';
				param.accept = 1;
			}
		}
		if (param.i == ind)
			break ;
	}
	if (!str[ind + 1] || str[ind + 1] == '$' || ft_isspace(str[ind + 1]))
		return (0);
	return (param.accept);
}

int	check_expansion(t_sub *sub, char *err_msg, int *syn_err)
{
	if (sub->invalid_expansion)
	{
		*syn_err = 2;
		return (exit_msg(NULL, err_msg, 1, EXIT_FAILURE));
	}
	return (0);
}

int	dc_count(t_sub **lst)
{
	t_sub	*temp;
	int		count;

	count = 0;
	if (lst && *lst)
	{
		count++;
		temp = *lst;
		while (temp->next != *lst)
		{
			count++;
			temp = temp->next;
		}
	}
	return (count);
}
