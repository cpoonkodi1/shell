/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:16:56 by pchennia          #+#    #+#             */
/*   Updated: 2024/08/01 09:16:36 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_args(t_sub *subs)
{
	int	args;

	args = 0;
	while (subs->cmd_arr[args + 1] != 0)
		args++;
	return (args);
}

int	change_entry(int args, char *str, int k)
{
	int	entry;

	entry = 1;
	ft_putstr_fd(str, STDOUT_FILENO);
	if (k < args)
	{
		ft_putstr_fd(" ", STDOUT_FILENO);
	}
	return (entry);
}

bool	has_otherthan_n(char *str)
{
	str++;
	while (*str)
	{
		if (*str != 'n')
		{
			return (true);
		}
		str++;
	}
	return (false);
}

void	display_echo(t_sub *subs)
{
	int	args;
	int	flag;
	int	k;
	int	entry;

	flag = 0;
	k = 1;
	entry = 0;
	args = find_args(subs);
	while (subs->cmd_arr[k] != 0)
	{
		if (ft_strcmp(subs->cmd_arr[k], "~") == 0)
			ft_putstr_fd(getenv("HOME"), STDOUT_FILENO);
		else if (subs->cmd_arr[k][0] == '-' \
			&& has_otherthan_n(subs->cmd_arr[k]) == false && entry != 1)
			flag = 1;
		else
			entry = change_entry(args, subs->cmd_arr[k], k);
		k++;
	}
	if (flag == 0)
		write(STDOUT_FILENO, "\n", 1);
}
