/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 04:18:38 by olmohame          #+#    #+#             */
/*   Updated: 2024/08/01 07:58:56 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	close_pipes_start(t_pipe *st_pipe, int id)
{
	int	i;
	int	err;

	i = -1;
	err = 0;
	while (++i < (st_pipe->num_cmd - 1))
	{
		if (i != (id - 1) && (st_pipe->pipes)[i][0] != -1)
		{
			if (close((st_pipe->pipes)[i][0]) == -1)
				err = 1;
			(st_pipe->pipes)[i][0] = -1;
		}
		if (i != id && (st_pipe->pipes)[i][1] != -1)
		{
			if (close((st_pipe->pipes)[i][1]) == -1)
				err = 1;
			(st_pipe->pipes)[i][1] = -1;
		}
	}
	return (err);
}

int	close_pipes(t_pipe *st_pipe, int id, int is_start)
{
	int	err;

	err = 0;
	if (!st_pipe || st_pipe->num_cmd == 1)
		return (0);
	if (is_start)
		err = close_pipes_start(st_pipe, id);
	if (is_start == 0 || is_start == 2)
	{
		if (id && (st_pipe->pipes)[id - 1][0] != -1)
		{
			if (close((st_pipe->pipes)[id - 1][0]) == -1)
				err = 1;
			(st_pipe->pipes)[id - 1][0] = -1;
		}
		if ((id != (st_pipe->num_cmd - 1)) && (st_pipe->pipes)[id][1] != -1)
		{
			if (close((st_pipe->pipes)[id][1]) == -1)
				err = 1;
			(st_pipe->pipes)[id][1] = -1;
		}
	}
	return (err);
}

static int	**build_pipe_mat(int pipe_num)
{
	int	i;
	int	**pipe_fd;

	i = -1;
	if (!pipe_num)
		return (NULL);
	pipe_fd = ft_calloc(pipe_num, sizeof(int *));
	if (!pipe_fd)
		return (NULL);
	while (++i < pipe_num)
	{
		pipe_fd[i] = ft_calloc(2, sizeof(int));
		if (!pipe_fd[i])
		{
			del_gen((void *)pipe_fd, i);
			pipe_fd = NULL;
			return (NULL);
		}
	}
	return (pipe_fd);
}

static int	init_pipe(t_shell **mshell)
{
	(*mshell)->st_pipe->path_name = NULL;
	(*mshell)->st_pipe->num_cmd = dc_count(&(*mshell)->subs);
	(*mshell)->st_pipe->num_children = 0;
	(*mshell)->st_pipe->pipes = build_pipe_mat((*mshell)->st_pipe->num_cmd - 1);
	(*mshell)->st_pipe->pids = \
			ft_calloc((*mshell)->st_pipe->num_cmd, sizeof(int));
	(*mshell)->st_pipe->cmd_paths = \
			ft_calloc((*mshell)->st_pipe->num_cmd, sizeof(char *));
	if ((!(*mshell)->st_pipe->pipes && (*mshell)->st_pipe->num_cmd != 1) \
			|| !(*mshell)->st_pipe->pids || !(*mshell)->st_pipe->cmd_paths)
		return (1);
	return (0);
}

int	new_pipe(t_shell **mshell)
{
	(*mshell)->st_pipe = (t_pipe *)malloc(sizeof(t_pipe));
	if (!(*mshell)->st_pipe || init_pipe(mshell))
	{
		exit(exit_msg(mshell, "Malloc failed.\n", 0, EXIT_FAILURE));
	}
	find_var(mshell, "PATH=");
	return (0);
}
