/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resourse_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 08:05:45 by olmohame          #+#    #+#             */
/*   Updated: 2024/08/01 07:55:06 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_middle(t_shell **shell, t_pipe *st_pipe, t_sub *sub, int id)
{
	int	fd_in;
	int	fd_out;

	fd_in = pick_fds(shell, 1, sub, id);
	fd_out = pick_fds(shell, 0, sub, id);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		wrapp_dup2(shell, sub, id);
	close(fd_in);
	if (fd_in == st_pipe->pipes[id - 1][0])
		st_pipe->pipes[id - 1][0] = -1;
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		wrapp_dup2(shell, sub, id);
	close(fd_out);
	if (fd_out == st_pipe->pipes[id][1])
		st_pipe->pipes[id][1] = -1;
}

static void	set_first(t_shell **shell, t_pipe *st_pipe, t_sub *sub, int id)
{
	int	fd_in;
	int	fd_out;

	if (sub->op_in != -1)
	{
		fd_in = sub->fd_in;
		is_valid_fd(shell, sub, id, fd_in);
		if (dup2(fd_in, STDIN_FILENO) == -1)
			wrapp_dup2(shell, sub, id);
		close(fd_in);
	}
	if (sub->op_out != -1)
	{
		fd_out = sub->fd_out;
		close(st_pipe->pipes[id][1]);
		st_pipe->pipes[id][1] = -1;
		is_valid_fd(shell, sub, id, fd_out);
	}
	else
		fd_out = st_pipe->pipes[id][1];
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		wrapp_dup2(shell, sub, id);
	close(fd_out);
	if (fd_out == st_pipe->pipes[id][1])
		st_pipe->pipes[id][1] = -1;
}

static void	set_last(t_shell **shell, t_pipe *st_pipe, t_sub *sub, int id)
{
	int	fd_in;
	int	fd_out;

	if (sub->op_in != -1)
	{
		fd_in = sub->fd_in;
		close(st_pipe->pipes[id - 1][0]);
		st_pipe->pipes[id - 1][0] = -1;
		is_valid_fd(shell, sub, id, fd_in);
	}
	else
		fd_in = st_pipe->pipes[id - 1][0];
	if (sub->op_out != -1)
	{
		fd_out = sub->fd_out;
		is_valid_fd(shell, sub, id, fd_out);
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			wrapp_dup2(shell, sub, id);
		close(fd_out);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
		wrapp_dup2(shell, sub, id);
	close(fd_in);
	if (fd_in == st_pipe->pipes[id - 1][0])
		st_pipe->pipes[id - 1][0] = -1;
}

static void	set_one_cmd(t_shell **shell, t_sub *sub, int id)
{
	int	fd_in;
	int	fd_out;

	if (sub->op_in != -1)
	{
		fd_in = sub->fd_in;
		is_valid_fd(shell, sub, id, fd_in);
		if (dup2(fd_in, STDIN_FILENO) == -1)
			wrapp_dup2(shell, sub, id);
		close(fd_in);
	}
	if (sub->op_out != -1)
	{
		fd_out = sub->fd_out;
		is_valid_fd(shell, sub, id, fd_out);
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			wrapp_dup2(shell, sub, id);
		close(fd_out);
	}
}

void	set_inout(t_shell **shell, t_pipe *st_pipe, t_sub *sub, int id)
{
	if ((*shell)->st_pipe->num_cmd == 1)
		set_one_cmd(shell, sub, id);
	else if (id == 0)
		set_first(shell, st_pipe, sub, id);
	else if ((*shell)->st_pipe->num_cmd == id + 1)
		set_last(shell, st_pipe, sub, id);
	else
		set_middle(shell, st_pipe, sub, id);
}
