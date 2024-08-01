/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 11:30:11 by pchennia          #+#    #+#             */
/*   Updated: 2024/07/31 11:04:26 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_cd_home(t_shell *mshell)
{
	char	*path;
	int		found;

	found = found_in_env("HOME=", mshell->curr_envp, &path);
	if (found && is_dir(path) == -1)
	{
		if (!path)
		{
			error_msg(CD, NO_FILE, path, mshell);
			mshell->execution_status = 1;
		}
	}
	else if (found)
		cd_update_in_env1(mshell, path);
	else
	{
		ft_putstr_fd(CD"HOME not set\n", STDERR_FILENO);
		mshell->execution_status = 1;
	}
	if (found)
		free(path);
}

void	exec_cd_oldpwd(t_shell *mshell)
{
	char	*path;

	if (found_in_env("OLDPWD=", mshell->curr_envp, &path) == 1)
	{
		cd_update_in_env1(mshell, path);
		display_pwd(mshell);
		free(path);
	}
	else
	{
		ft_putstr_fd(CD"OLDPWD not set\n", STDERR_FILENO);
		mshell->execution_status = 1;
	}
}

void	exec_cd_tilde(t_shell *mshell)
{
	char	*path;
	int		found;

	found = found_in_env("HOME=", mshell->curr_envp, &path);
	if (found && is_dir(path) == -1)
	{
		if (!path)
		{
			error_msg(CD, NO_FILE, path, mshell);
			mshell->execution_status = 1;
		}
	}
	else if (found)
		cd_update_in_env1(mshell, path);
	else
		cd_update_in_env1(mshell, mshell->homepath);
	if (found)
		free(path);
}

void	handle_cd_else(t_shell *mshell, t_sub *subs)
{
	if (access(subs->cmd_arr[1], F_OK) == 0 && !is_dir(subs->cmd_arr[1]))
		cd_update_in_env1(mshell, subs->cmd_arr[1]);
	else if (is_dir(subs->cmd_arr[1]) == 1)
	{
		error_msg(CD, ": Not a directory\n", subs->cmd_arr[1], mshell);
		mshell->execution_status = 1;
	}
	else
	{
		error_msg(CD, NO_FILE, subs->cmd_arr[1], mshell);
		mshell->execution_status = 1;
	}
}

void	exec_cd(t_shell *mshell, t_sub *subs)
{
	mshell->execution_status = 0;
	if (subs->cmd_arr[1] == NULL || ft_strcmp(subs->cmd_arr[1], "--") == 0)
		exec_cd_home(mshell);
	else if (ft_strcmp(subs->cmd_arr[1], "~") == 0)
		exec_cd_tilde(mshell);
	else if (ft_strcmp(subs->cmd_arr[1], "-") == 0)
		exec_cd_oldpwd(mshell);
	else if (subs->cmd_arr[2])
	{
		if (check_isdigit(subs->cmd_arr[2]))
		{
			ft_putstr_fd(CD"too many arguments\n", STDERR_FILENO);
			mshell->execution_status = 1;
		}
		else
			check_arg_two(mshell, subs);
	}
	else
		handle_cd_else(mshell, subs);
}
