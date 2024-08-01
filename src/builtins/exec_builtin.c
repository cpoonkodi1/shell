/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 11:30:47 by pchennia          #+#    #+#             */
/*   Updated: 2024/08/01 09:16:29 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child_process_builtin(t_shell *mshell, t_pipe *st_pipe, \
t_sub *sub, int id)
{
	if (!sub->cmd_arr[0])
	{
		close_pipes(st_pipe, id, 2);
		close_files(&sub, 0, 2);
		exit(exit_msg(&mshell, "", 0, 0));
	}
	execute_builtin_cmd(mshell, st_pipe, sub, id);
	exit(exit_msg(&mshell, "", 0, mshell->execution_status));
}

bool	is_builtin_cmd(const char *command)
{
	if (0 == ft_strcmp("cd", command))
		return (true);
	else if (0 == ft_strcmp("exit", command))
		return (true);
	else if (0 == ft_strcmp("export", command))
		return (true);
	else if (0 == ft_strcmp("unset", command))
		return (true);
	else if (0 == ft_strcmp("echo", command))
		return (true);
	else if (0 == ft_strcmp("env", command))
		return (true);
	else if (0 == ft_strcmp("pwd", command))
		return (true);
	return (false);
}

void	exec_cmd(t_shell *mshell, t_sub *subs)
{
	if (!ft_strcmp(subs->cmd_arr[0], "echo"))
	{
		if (subs->op_in != -1 && subs->fd_in == -1)
		{
			mshell->execution_status = 1;
			return ;
		}
		else
			display_echo(subs);
	}	
	else if (!ft_strcmp(subs->cmd_arr[0], "pwd"))
		display_pwd(mshell);
	else if (!ft_strcmp(subs->cmd_arr[0], "env"))
		display_env(mshell, subs);
	else if (!ft_strcmp(subs->cmd_arr[0], "cd"))
		exec_cd(mshell, subs);
	else if (!ft_strcmp(subs->cmd_arr[0], "unset"))
		exec_unset(mshell, subs);
	else if (!ft_strcmp(subs->cmd_arr[0], "export"))
		exec_export(mshell, subs->cmd_arr);
}

int	execute_builtin_cmd(t_shell *mshell, t_pipe *st_pipe, t_sub *subs, int id)
{
	int	dupe_stdout;

	mshell->execution_status = 0;
	if (subs->op_out != -1 && subs->fd_out == -1)
	{
		close_input(mshell->st_pipe, subs, id);
		bi_close_all_pipes(mshell->st_pipe);
		return (mshell->execution_status = 1);
	}
	bi_set_output(st_pipe, subs, id, &dupe_stdout);
	exec_cmd(mshell, subs);
	if (!ft_strcmp(subs->cmd_arr[0], "exit"))
	{
		if (exec_exit(mshell, subs))
		{
			close_inout(mshell, subs, id, &dupe_stdout);
			return (1);
		}
	}
	close_inout(mshell, subs, id, &dupe_stdout);
	return (mshell->execution_status);
}
