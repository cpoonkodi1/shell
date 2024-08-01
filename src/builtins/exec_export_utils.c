/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:42:27 by pchennia          #+#    #+#             */
/*   Updated: 2024/07/31 11:05:26 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_special_char(char c)
{
	if (c == ' ' || c == '%' || c == '?' || c == ':' || c == '#'
		|| (c >= 42 && c <= 47))
	{
		return (1);
	}
	return (0);
}

int	check_first_char(char c)
{
	int	is_digit;

	is_digit = ft_isdigit(c);
	if (c == '=' || c == ' ' || is_digit == 1)
		return (1);
	else
		return (0);
}

int	check_brace(char c)
{
	if (c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']')
	{
		ft_putstr_fd(MS"syntax error near unexpected token `", STDERR_FILENO);
		ft_putchar_fd(c, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	validate_identifier(char *before_eq, char *original_str)
{
	int	i;

	i = 0;
	while (before_eq[i] != '\0')
	{
		if (check_brace(before_eq[i]))
		{
			free(before_eq);
			return (1);
		}
		else if (check_special_char(before_eq[i]))
		{
			free(before_eq);
			print_err(EXPORT, original_str, ": not a valid identifier\n");
			return (1);
		}
		i++;
	}
	free(before_eq);
	return (0);
}

int	check_identifier(t_shell *mshell, char *str)
{
	int		len;
	char	*equal_pos;
	char	*before_eq;

	equal_pos = ft_strchr(str, '=');
	if (equal_pos != NULL)
	{
		len = equal_pos - str;
		before_eq = (char *)malloc(len + 1);
		if (!before_eq)
			exit(exit_msg(&mshell, "Malloc failed.\n", 0, EXIT_FAILURE));
		ft_strncpy(before_eq, str, len);
		before_eq[len] = '\0';
		return (validate_identifier(before_eq, str));
	}
	return (0);
}
