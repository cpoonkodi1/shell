/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 23:31:09 by pchennia          #+#    #+#             */
/*   Updated: 2024/07/31 11:03:35 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_inout(t_shell *mshell, t_sub *sub, int index, \
int *dupe_stdout)
{
	close_output(mshell, sub, index, dupe_stdout);
	close_input(mshell->st_pipe, sub, index);
	bi_close_all_pipes(mshell->st_pipe);
}

int	bi_set_output(t_pipe *st_pipe, t_sub *sub, int index, \
int *dupe_stdout)
{
	int	fd_out;
	int	status;

	status = 0;
	if (sub->op_out != -1)
	{
		fd_out = sub->fd_out;
		*dupe_stdout = dup(STDOUT_FILENO);
		status = dup2(fd_out, STDOUT_FILENO);
	}
	else if (st_pipe->num_cmd != (index + 1))
	{
		*dupe_stdout = dup(STDOUT_FILENO);
		fd_out = st_pipe->pipes[index][1];
		status = dup2(fd_out, STDOUT_FILENO);
	}
	else
		*dupe_stdout = -1;
	return (status);
}

int	close_output(t_shell *mshell, t_sub *sub, int index, \
int *dupe_stdout)
{
	int	status;

	status = 0;
	if (sub->op_out != -1)
	{
		status = close(sub->fd_out);
		sub->fd_out = -1;
	}
	if (mshell->st_pipe->num_cmd != (index + 1))
	{
		status = close(mshell->st_pipe->pipes[index][1]);
		mshell->st_pipe->pipes[index][1] = -1;
	}
	if (*dupe_stdout != -1)
	{
		if (dup2(*dupe_stdout, STDOUT_FILENO) == -1)
			wrapp_dup2(&mshell, sub, index);
		close(*dupe_stdout);
		*dupe_stdout = -1;
	}
	return (status);
}

int	close_input(t_pipe *st_pipe, t_sub *sub, int index)
{
	int		status;

	status = 0;
	if (sub->op_in != -1)
	{
		status = close(sub->fd_in);
		sub->fd_in = -1;
	}
	if (st_pipe->num_cmd != (index + 1))
	{
		status = close(st_pipe->pipes[index][0]);
		st_pipe->pipes[index][0] = -1;
	}
	return (status);
}

void	bi_close_all_pipes(t_pipe *st_pipe)
{
	int	i;
	int	*fd;

	i = 0;
	if (st_pipe == NULL)
		return ;
	while (i < st_pipe->num_cmd - 1)
	{
		fd = st_pipe->pipes[i];
		if (fd != NULL)
		{
			if (fd[0] != -1)
			{
				close(fd[0]);
				fd[0] = -1;
			}
			if (fd[1] != -1)
			{
				close(fd[1]);
				fd[1] = -1;
			}
		}
		i++;
	}
}
