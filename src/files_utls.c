/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 06:31:57 by olmohame          #+#    #+#             */
/*   Updated: 2024/08/01 07:54:25 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_files_sub(t_sub *sub, int is_parent)
{
	if (sub->fd_in != -1)
	{
		close(sub->fd_in);
		sub->fd_in = -1;
		if (is_parent && sub->op_in == 2)
			unlink(sub->fname_in);
	}
	if (sub->fd_out != -1)
	{
		close(sub->fd_out);
		sub->fd_out = -1;
	}
}

int	close_files(t_sub **lst, int is_parent, int is_start)
{
	t_sub	*sub;

	if (lst && *lst)
	{
		sub = *lst;
		if (is_start == 0 || is_start == 2)
		{
			close_files_sub(sub, is_parent);
		}
		if (is_start == 1 || is_start == 2)
		{
			while (sub->next != *lst)
			{
				sub = sub->next;
				close_files_sub(sub, is_parent);
			}
		}
		return (0);
	}
	return (1);
}

int	pick_fds(t_shell **shell, int get_input_fd, t_sub *sub, int id)
{
	int	chosen_fd;

	if (get_input_fd)
	{
		if (sub->op_in != -1)
		{
			chosen_fd = sub->fd_in;
			close((*shell)->st_pipe->pipes[id - 1][0]);
			(*shell)->st_pipe->pipes[id - 1][0] = -1;
			is_valid_fd(shell, sub, id, chosen_fd);
		}
		else
			chosen_fd = (*shell)->st_pipe->pipes[id - 1][0];
		return (chosen_fd);
	}
	if (sub->op_out != -1)
	{
		chosen_fd = sub->fd_out;
		close((*shell)->st_pipe->pipes[id][1]);
		(*shell)->st_pipe->pipes[id][1] = -1;
		is_valid_fd(shell, sub, id, chosen_fd);
	}
	else
		chosen_fd = (*shell)->st_pipe->pipes[id][1];
	return (chosen_fd);
}

void	is_valid_fd(t_shell **shell, t_sub *sub, int id, int fd)
{
	if (fd == -1)
	{
		close_files(&sub, 0, 2);
		close_pipes((*shell)->st_pipe, id, 2);
		exit(exit_msg(shell, "", 0, EXIT_FAILURE));
	}
}

void	wrapp_dup2(t_shell **shell, t_sub *sub, int id)
{
	perror("minishell:");
	close_files(&sub, 0, 2);
	close_pipes((*shell)->st_pipe, id, 2);
	exit(exit_msg(shell, "", 0, EXIT_FAILURE));
}
