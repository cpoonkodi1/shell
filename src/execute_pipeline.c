/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 05:26:06 by olmohame          #+#    #+#             */
/*   Updated: 2024/08/01 08:01:05 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child_process(t_shell *mshell, t_pipe *st_pipe, t_sub *sub, int id)
{
	char	*msg;
	int		exit_code;

	set_inout(&mshell, st_pipe, sub, id);
	if (!sub->cmd_arr[0])
	{
		close_pipes(st_pipe, id, 2);
		close_files(&sub, 0, 2);
		exit(exit_msg(&mshell, "", 0, 0));
	}
	if (close_pipes(st_pipe, id, 1) || close_files(&sub, 0, 1))
		exit(exit_msg(&mshell, "Stopping execution.", 0, 1));
	build_path(mshell, st_pipe, sub, id);
	exit_code = 1;
	execve(st_pipe->cmd_paths[id], sub->cmd_arr, mshell->curr_envp);
	exit_code += 126 * (errno == ENONET) + 125 * (errno == EACCES);
	msg = prep_msg(&mshell, "minishell: ", sub->cmd_arr[0], "");
	perror(msg);
	free(msg);
	close_pipes(st_pipe, id, 2);
	close_files(&sub, 0, 2);
	exit(exit_msg(&mshell, "", 0, exit_code));
}

void	run_process(t_shell *mshell, t_sub	*subs, t_pipe *st_pipe, int i)
{
	int	j;

	if (st_pipe->pids[i] == 0)
	{
		j = -1;
		mshell->unlink_file = 0;
		while (++j < i)
			subs = subs->next;
		if (!subs->cmd_arr[0] || !is_builtin_cmd(subs->cmd_arr[0]))
			child_process(mshell, st_pipe, subs, i);
		else
			child_process_builtin(mshell, st_pipe, subs, i);
	}
}

int	start_children(t_shell *mshell, t_pipe *st_pipe)
{
	int		i;
	t_sub	*subs;

	if (!st_pipe)
		return (0);
	i = -1;
	subs = mshell->subs;
	while (++i < st_pipe->num_cmd)
	{
		if (st_pipe->num_cmd == 1 && subs->cmd_arr[0] \
								&& is_builtin_cmd(subs->cmd_arr[0]))
		{
			execute_builtin_cmd(mshell, st_pipe, subs, i);
			return (0);
		}
		st_pipe->pids[i] = fork();
		if (st_pipe->pids[i] == -1)
		{
			perror("minishell: fork");
			mshell->execution_status = 1;
			break ;
		}
		run_process(mshell, subs, st_pipe, i);
	}
	return (i);
}

static void	parent_process(t_shell *mshell, t_pipe *st_pipe)
{
	int					i;

	st_pipe->num_children = start_children(mshell, st_pipe);
	close_pipes(st_pipe, 0, 2);
	i = -1;
	while (++i < st_pipe->num_children)
	{
		process_exit_code(mshell, i);
	}
	close_files(&mshell->subs, 1, 2);
	return ;
}

void	executer(t_shell *mshell)
{
	ssize_t				i;
	struct sigaction	sa;

	sa.sa_handler = &sig_handler_pipex_and_heredoc;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	i = -1;
	find_var(&mshell, "PATH=");
	while (++i < (mshell->st_pipe->num_cmd - 1))
	{
		if (pipe(mshell->st_pipe->pipes[i]) == -1)
		{
			perror("minishell: pipe");
			close_pipes(mshell->st_pipe, mshell->st_pipe->num_cmd, 2);
			close_files(&(mshell->subs), 1, 2);
			exit(exit_msg(&mshell, "", 0, EXIT_FAILURE));
		}
	}
	parent_process(mshell, mshell->st_pipe);
}
