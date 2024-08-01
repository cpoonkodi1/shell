/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 05:09:51 by olmohame          #+#    #+#             */
/*   Updated: 2024/08/01 05:32:34 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	separate_cmd_path(t_shell *mshell, t_pipe *st_pipe, \
													t_sub *sub, int id)
{
	int		len;
	char	*temp;

	st_pipe->cmd_paths[id] = ft_strdup(sub->cmd_arr[0]);
	if (!st_pipe->cmd_paths[id])
	{
		close_pipes(st_pipe, id, 0);
		close_files(&sub, 0, 0);
		exit(exit_msg(&mshell, "Malloc failed.\n", 0, EXIT_FAILURE));
	}
	len = ft_strrchr(sub->cmd_arr[0], '/') - sub->cmd_arr[0] + 1;
	temp = ft_substr(sub->cmd_arr[0], len, \
						ft_strlen(sub->cmd_arr[0]));
	if (!temp)
	{
		free(st_pipe->cmd_paths[id]);
		st_pipe->cmd_paths[id] = NULL;
		close_pipes(st_pipe, id, 0);
		close_files(&sub, 0, 0);
		exit(exit_msg(&mshell, "Malloc failed.\n", 0, EXIT_FAILURE));
	}
	free(sub->cmd_arr[0]);
	sub->cmd_arr[0] = temp;
	return (0);
}

static int	check_given_path(t_shell *mshell, \
							t_pipe *st_pipe, t_sub *sub, int id)
{
	char	*msg;
	int		exit_code;

	exit_code = 1;
	if (!st_pipe || !st_pipe->cmd_paths)
		return (EXIT_FAILURE);
	if (!sub || !(sub->cmd_arr))
		return (EXIT_FAILURE);
	if (sub->cmd_arr[0] && !ft_strchr(sub->cmd_arr[0], '/'))
		return (EXIT_FAILURE);
	if (is_valid_filepath(mshell, st_pipe, sub, id))
		return (EXIT_FAILURE);
	separate_cmd_path(mshell, st_pipe, sub, id);
	if (!access(st_pipe->cmd_paths[id], F_OK | X_OK))
		return (0);
	if (access(st_pipe->cmd_paths[id], F_OK) == -1)
		exit_code = 127;
	else if (access(st_pipe->cmd_paths[id], X_OK) == -1)
		exit_code = 126;
	msg = prep_msg(&mshell, "minishell: ", st_pipe->cmd_paths[id], "");
	perror(msg);
	free(msg);
	close_pipes(st_pipe, id, 0);
	close_files(&sub, 0, 0);
	exit(exit_msg(&mshell, "", 0, exit_code));
}

static int	check_empty_path(t_shell *mshell, \
								t_pipe *st_pipe, t_sub *sub, int id)
{
	char	*msg;
	int		exit_code;

	if (!st_pipe->cmd_paths[id] || ft_strlen(sub->cmd_arr[0]) == 0)
	{
		exit_code = 127;
		free(st_pipe->pids);
		st_pipe->pids = NULL;
		msg = prep_msg(&mshell, "", sub->cmd_arr[0], ": command not found\n");
		close_pipes(st_pipe, id, 0);
		close_files(&sub, 0, 0);
		exit(exit_msg(&mshell, msg, 1, exit_code));
	}
	return (1);
}

static int	construct_path(t_shell *mshell, \
								char **path_split, t_sub *sub, int id)
{
	int		i;

	i = -1;
	while (path_split[++i])
	{
		mshell->st_pipe->cmd_paths[id] = ft_strsepjoin(path_split[i], \
								'/', sub->cmd_arr[0]);
		if (!mshell->st_pipe->cmd_paths[id])
		{
			ft_del(path_split, ft_count(mshell->st_pipe->path_name, ':'));
			path_split = NULL;
			close_files(&sub, 0, 0);
			close_pipes(mshell->st_pipe, id, 0);
			exit(exit_msg(&mshell, "Malloc failed.\n", 0, EXIT_FAILURE));
		}
		if (!access (mshell->st_pipe->cmd_paths[id], F_OK))
			break ;
		free(mshell->st_pipe->cmd_paths[id]);
		mshell->st_pipe->cmd_paths[id] = NULL;
	}
	return (0);
}

int	build_path(t_shell *mshell, t_pipe *st_pipe, t_sub *sub, int id)
{
	char	**path_split;

	if ((st_pipe->path_name != NULL) && \
					check_given_path(mshell, st_pipe, sub, id))
	{
		if (!ft_strcmp(sub->cmd_arr[0], "..") || \
								!ft_strcmp(sub->cmd_arr[0], "."))
		{
			mshell->st_pipe->cmd_paths[id] = NULL;
			return (check_empty_path(mshell, st_pipe, sub, id));
		}
		path_split = ft_split(st_pipe->path_name, ':');
		if (!path_split)
		{
			close_files(&sub, 0, 0);
			close_pipes(st_pipe, id, 0);
			exit(exit_msg(&mshell, "Malloc failed.\n", 0, EXIT_FAILURE));
		}
		construct_path(mshell, path_split, sub, id);
		ft_del(path_split, ft_count(st_pipe->path_name, ':'));
		path_split = NULL;
	}
	return (check_empty_path(mshell, st_pipe, sub, id));
}
