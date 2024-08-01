/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 11:30:33 by pchennia          #+#    #+#             */
/*   Updated: 2024/07/31 11:05:40 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export_declare(char **env)
{
	int	i;
	int	first_eq;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "_=", 2) != 0)
		{
			ft_putstr_fd("declare -x ", 1);
			if (find_equal(env[i], &first_eq) == 0)
				ft_putendl_fd(env[i], STDOUT_FILENO);
			else
				print_variable_with_quotes(env[i]);
		}
		i++;
	}
}

int	check_if_env_has_given_var(char **env, char *var_only)
{
	int		i;
	size_t	var_len;

	i = 0;
	var_len = ft_strlen(var_only);
	while (env[i])
	{
		if (ft_strncmp(env[i], var_only, var_len) == 0
			&& (env[i][var_len] == '=' || env[i][var_len] == '\0'))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	**find_and_delete_if_exist(char **env, char *cmdargs)
{
	int		found;
	char	var_only[256];

	found = 0;
	if (cmdargs)
	{
		if (find_equal(cmdargs, &found) != 0)
		{
			strncpy(var_only, cmdargs, found);
			var_only[found] = '\0';
			if (check_if_env_has_given_var(env, var_only))
				env = del_var_declare(env, var_only);
		}
	}
	return (env);
}

void	handle_envs(char *str, t_shell *mshell)
{
	char	**updated_declare;
	char	**updated_env;

	if (check_some_conditions(mshell, str) == 1)
		mshell->execution_status = 1;
	else
	{
		if (!(ft_strchr(str, '=')) && !(ft_strlen(str) == 0))
		{
			if (!check_if_env_has_given_var(mshell->declare_env, str))
			{
				updated_declare = add_var(mshell->declare_env, str, mshell);
				exit_free_assign(mshell, updated_declare, 'd');
			}
		}
		else if (ft_strchr(str, '='))
		{
			updated_declare = add_var(mshell->declare_env, str, mshell);
			exit_free_assign(mshell, updated_declare, 'd');
			updated_env = add_var(mshell->curr_envp, str, mshell);
			exit_free_assign(mshell, updated_env, 'c');
		}
	}
}

void	exec_export(t_shell *mshell, char **cmdargs)
{
	int		i;
	char	**tmp;
	char	**env;

	mshell->execution_status = 0;
	if (!cmdargs[1])
	{
		export_declare(mshell->declare_env);
		return ;
	}
	i = 1;
	while (cmdargs[i])
	{
		env = find_and_delete_if_exist(mshell->curr_envp, cmdargs[i]);
		exit_free_assign(mshell, env, 'c');
		tmp = find_and_delete_if_exist(mshell->declare_env, cmdargs[i]);
		exit_free_assign(mshell, tmp, 'd');
		handle_envs(cmdargs[i], mshell);
		i++;
	}
}
