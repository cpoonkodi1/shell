/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 11:30:23 by pchennia          #+#    #+#             */
/*   Updated: 2024/08/01 10:38:32 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_atoi_exit(const char *str, long *nbr)
{
	unsigned int	i;
	int				sign;

	i = 0;
	sign = 1;
	*nbr = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		*nbr = *nbr * 10 + str[i] - '0';
		i++;
	}
	if (!str[i])
	{
		return (*nbr *= sign, 0);
	}
	return (-1);
}

int	is_only_exit(t_shell *mshell, t_sub *subs)
{
	if (!subs->cmd_arr[1])
	{
		mshell->execution_status = 0;
		mshell->should_exit = true;
		return (1);
	}
	return (0);
}

int	exec_exit(t_shell *mshell, t_sub *subs)
{
	long	nbr;

	nbr = 0;
	printf("exit\n");
	if (is_only_exit(mshell, subs))
		return (1);
	if (ft_atoi_exit(subs->cmd_arr[1], &nbr) < 0)
	{
		error_msg(E_EXIT, NUM, subs->cmd_arr[1], mshell);
		mshell->execution_status = 2;
		mshell->should_exit = true;
		return (mshell->execution_status);
	}
	else if (subs->cmd_arr[2])
	{
		ft_putstr_fd(E_EXIT"too many arguments\n", STDERR_FILENO);
		mshell->execution_status = 1;
	}
	else
	{
		mshell->execution_status = nbr % 256;
		mshell->should_exit = true;
	}
	return (1);
}
