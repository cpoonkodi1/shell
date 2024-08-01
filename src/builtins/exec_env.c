/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:34:25 by pchennia          #+#    #+#             */
/*   Updated: 2024/08/01 09:03:38 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	write_env(t_shell *mshell, t_sub *subs)
{
	int	i;

	if (!subs->cmd_arr[1])
	{
		i = 0;
		while (mshell->curr_envp[i])
		{
			ft_putendl_fd(mshell->curr_envp[i], STDOUT_FILENO);
			i++;
		}
	}
}

void	display_env_error(t_shell *mshell, char *cmd, int status)
{
	if (status == 0)
	{
		error_msg(MS, OP, cmd, mshell);
		mshell->execution_status = 0;
	}
	else if (status == 127)
	{
		error_msg(ENV, NO_FILE, cmd, mshell);
		mshell->execution_status = 127;
	}
}

void	display_env(t_shell *mshell, t_sub *subs)
{
	int	i;

	i = 1;
	while (subs->cmd_arr[i])
	{
		if (ft_strcmp(subs->cmd_arr[i], "pwd") == 0
			&& subs->cmd_arr[i + 1] != 0)
		{
			ft_putstr_fd(IG_MSG, STDERR_FILENO);
			display_pwd(mshell);
			return ;
		}
		else if (ft_strcmp(subs->cmd_arr[i], "pwd") == 0 \
				&& subs->cmd_arr[i + 1] == NULL)
		{
			display_pwd(mshell);
			return ;
		}
		else if (subs->cmd_arr[1][0] == '-')
			display_env_error(mshell, subs->cmd_arr[1], 0);
		else
			display_env_error(mshell, subs->cmd_arr[1], 127);
		i++;
	}
	write_env(mshell, subs);
}
