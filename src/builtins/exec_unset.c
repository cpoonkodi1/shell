/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 11:30:40 by pchennia          #+#    #+#             */
/*   Updated: 2024/08/01 06:53:01 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	fill_env_excluding_var(char **new_env, char **env, char *var_only,
size_t	var_len)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (!(ft_strncmp(env[i], var_only, var_len) == 0 && \
				(env[i][var_len] == '=' || env[i][var_len] == '\0')))
		{
			new_env[j] = ft_strdup(env[i]);
			if (!new_env[j])
				return (1);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (0);
}

char	**copy_env_without_specified_var_to_env(int found, char **env, \
char **envcpy)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (i != found)
		{
			envcpy[j] = ft_strdup(env[i]);
			i++;
			j++;
		}
		else
			i++;
	}
	return (envcpy);
}

/* 	deletes the var and returns a copy of env
	if not found, returns env */
char	**env_excluding_var(char **env, char *var)
{
	int		i;
	int		len;
	char	**env_without_specified_var;
	char	*var_with_equal;

	i = 0;
	var_with_equal = ft_strjoin(var, "=");
	i = find_index(env, var_with_equal);
	if (env[i] == NULL)
	{
		free(var_with_equal);
		return (env);
	}
	free(var_with_equal);
	len = 0;
	while (env[len])
		len++;
	env_without_specified_var = malloc(sizeof(char *) * (len));
	if (env_without_specified_var == NULL)
		return (NULL);
	env_without_specified_var[len - 1] = NULL;
	copy_env_without_specified_var_to_env(i, env, env_without_specified_var);
	return (env_without_specified_var);
}

char	**del_var_declare(char **env, char *var_only)
{
	size_t	var_len;
	int		env_count;
	char	**new_env;
	int		result;

	var_len = ft_strlen(var_only);
	env_count = count_env_vars(env);
	new_env = malloc((env_count + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	result = fill_env_excluding_var(new_env, env, var_only, var_len);
	if (result)
	{
		free_env(new_env);
		return (NULL);
	}
	return (new_env);
}

void	exec_unset(t_shell *mshell, t_sub *subs)
{
	int		i;
	char	**env;
	char	**tmp;

	i = 1;
	while (mshell->subs->cmd_arr[i])
	{
		env = env_excluding_var(mshell->curr_envp, subs->cmd_arr[i]);
		exit_free_assign(mshell, env, 'c');
		tmp = del_var_declare(mshell->declare_env, subs->cmd_arr[i]);
		exit_free_assign(mshell, tmp, 'd');
		i++;
	}
	mshell->execution_status = 0;
}
