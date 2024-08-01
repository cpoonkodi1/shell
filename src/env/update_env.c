/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 01:54:56 by pchennia          #+#    #+#             */
/*   Updated: 2024/07/31 11:52:03 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_free_assign(t_shell *mshell, char **temp_env, char c)
{
	if (c == 'c')
	{
		if (temp_env == NULL)
			exit(exit_msg(&mshell, MF, 0, EXIT_FAILURE));
		if (temp_env != mshell->curr_envp)
		{
			free_env(mshell->curr_envp);
			mshell->curr_envp = temp_env;
		}
	}
	else if (c == 'd')
	{
		if (temp_env == NULL)
			exit(exit_msg(&mshell, MF, 0, EXIT_FAILURE));
		if (temp_env != mshell->declare_env)
		{
			free_env(mshell->declare_env);
			mshell->declare_env = temp_env;
		}
	}
}

void	update_oldpwd1(char *old_pwd, t_shell *mshell)
{
	char	*var;
	char	**envcpy;

	var = ft_strjoin("OLDPWD=", old_pwd);
	if (!var)
		return ;
	envcpy = env_excluding_var(mshell->curr_envp, "OLDPWD");
	exit_free_assign(mshell, envcpy, 'c');
	envcpy = add_var(mshell->curr_envp, var, mshell);
	exit_free_assign(mshell, envcpy, 'c');
	free(var);
}

void	update_pwd1(t_shell *mshell)
{
	char	*pwd;
	char	*var;
	char	**envcpy;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		getcwd_err_msg();
		return ;
	}
	var = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (!var)
		return ;
	envcpy = env_excluding_var(mshell->curr_envp, "PWD");
	exit_free_assign(mshell, envcpy, 'c');
	envcpy = add_var(mshell->curr_envp, var, mshell);
	exit_free_assign(mshell, envcpy, 'c');
	free(var);
}

void	cd_update_in_env1(t_shell *mshell, char *path)
{
	char	*old_pwd;
	int		status;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		getcwd_err_msg();
		return ;
	}
	update_oldpwd1(old_pwd, mshell);
	free(old_pwd);
	status = chdir(path);
	if (status == 0)
		mshell->execution_status = 0;
	else
		mshell->execution_status = 1;
	update_pwd1(mshell);
}
