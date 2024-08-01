/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 05:59:28 by olmohame          #+#    #+#             */
/*   Updated: 2024/07/12 04:44:32 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_file(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
	{
		return (-1);
	}
	return (S_ISREG(path_stat.st_mode));
}

int	is_valid_filepath(t_shell *mshell, t_pipe *st_pipe, t_sub *sub, int id)
{
	char	*msg;
	int		exit_code;
	int		ret;

	exit_code = 127;
	ret = is_file(sub->cmd_arr[0]);
	if (ret == -1)
	{
		msg = prep_msg(&mshell, "minishell: ", sub->cmd_arr[0], "");
		perror(msg);
		free(msg);
		close_pipes(st_pipe, id, 0);
		close_files(&sub, 0, 0);
		exit(exit_msg(&mshell, "", 0, exit_code));
	}
	if (!ret)
	{
		exit_code = 126;
		msg = prep_msg(&mshell, "minishell: ", \
						sub->cmd_arr[0], ": Is a directory\n");
		close_pipes(st_pipe, id, 0);
		close_files(&sub, 0, 0);
		exit(exit_msg(&mshell, msg, 1, exit_code));
	}
	return (0);
}

int	del_tokens(t_sub *sub)
{
	ssize_t	i;

	i = -1;
	if (sub && sub->cmd_arr)
	{
		while (sub->cmd_arr[++i])
		{
			free(sub->cmd_arr[i]);
			sub->cmd_arr[i] = NULL;
		}
		free(sub->cmd_arr);
		sub->cmd_arr = NULL;
		return (0);
	}
	return (1);
}
