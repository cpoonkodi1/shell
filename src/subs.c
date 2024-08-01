/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 06:08:15 by olmohame          #+#    #+#             */
/*   Updated: 2024/07/28 10:11:30 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	spaces(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (i == ft_strlen(str))
		return (1);
	return (0);
}

static int	register_state(char *str, t_param *param)
{
	int	diff;

	diff = param->prev_red - str[param->i];
	if (in(str[param->i], "<>") && !is_quoted(str, param->i))
	{
		if (param->prev_red && \
			(diff != 0 || str[param->i - 1] != str[param->i]))
		{
			str[param->i + 1] = 0;
			return (exit_msg(NULL, prep_msg(NULL, "syntax error near "\
			"unexpected token `", str + param->i, "\'\n"), 1, EXIT_FAILURE));
		}
		param->prev_red += str[param->i];
		param->accept = 0;
		if (spaces(str + param->i + 1))
			return (exit_msg(NULL, "minishell: syntax error near" \
				" unexpected token `newline'\n", 0, EXIT_FAILURE));
	}
	else if (!(ft_isspace(str[param->i]) || in(str[param->i], "|")))
	{
		param->prev_red = 0;
		param->accept = 1;
	}
	return (0);
}

static int	create_sub(t_shell **mshell, t_sub **head, \
											char *str, t_param *param)
{
	int	ret;

	ret = 0;
	if (in(str[param->i], "|") && !is_quoted(str, param->i))
	{
		if (param->accept && !spaces(str + param->i + 1) && !param->prev_red)
		{
			ret = add_sub(head, str, param->start_index, param->i);
			param->start_index = param->i + 1;
			param->accept = 0;
			param->prev_red = 0;
		}
		else
		{
			return (exit_msg(NULL, "minishell: syntax error" \
			" near unexpected token `|'\n", 0, EXIT_FAILURE));
		}
	}
	else if (!str[param->i + 1])
		ret = add_sub(head, str, param->start_index, param->i + 1);
	(*mshell)->subs = *head;
	if (ret)
		exit(exit_msg(mshell, "", 0, EXIT_FAILURE));
	return (0);
}

static void	init_param(t_param *param)
{
	param->i = -1;
	param->start_index = 0;
	param->accept = 0;
	param->prev_red = 0;
}

int	build_subs(t_shell *mshell, char *str)
{
	t_param	param;
	t_sub	*head;

	init_param(&param);
	head = NULL;
	while (str[++(param.i)])
	{
		mshell->subs = head;
		if (register_state(str, &param))
		{
			mshell->subs = head;
			return (1);
		}
		if (create_sub(&mshell, &head, str, &param))
		{
			mshell->subs = head;
			return (1);
		}
	}
	mshell->subs = head;
	if (is_quoted(str, param.i))
		exit_msg(NULL, "minishell: Syntax error,"\
		" stopping execution\n", 0, EXIT_FAILURE);
	return (is_quoted(str, param.i));
}
