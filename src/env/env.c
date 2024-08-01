/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 23:45:52 by pchennia          #+#    #+#             */
/*   Updated: 2024/07/31 11:02:18 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_first_char1(char c)
{
	int	is_digit;

	is_digit = ft_isdigit(c);
	if (is_digit == 1)
		return (1);
	else
		return (0);
}

int	check_env_with_new_var(char **env_with_new_var, int i, char *var)
{
	if (env_with_new_var)
	{
		env_with_new_var[i] = ft_strdup(var);
		if (env_with_new_var[i] == NULL)
		{
			return (1);
		}
	}
	return (0);
}

int	copy_contents(int i, int len, char **env, char **env_with_new_var)
{
	while (i < len)
	{
		env_with_new_var[i] = ft_strdup(env[i]);
		if (env_with_new_var[i] == NULL)
		{
			free_env(env_with_new_var);
			env_with_new_var = NULL;
			break ;
		}
		i++;
	}
	return (i);
}

char	**add_var(char **env, char *var, t_shell *mshell)
{
	int		len;
	int		i;
	int		result;
	char	**env_with_new_var;

	len = 0;
	while (env[len])
		len++;
	env_with_new_var = malloc(sizeof(char *) * (len + 2));
	if (!env_with_new_var)
		exit(exit_msg(&mshell, "Malloc failed.\n", 0, EXIT_FAILURE));
	env_with_new_var[len + 1] = NULL;
	i = 0;
	i = copy_contents(i, len, env, env_with_new_var);
	result = check_env_with_new_var(env_with_new_var, i, var);
	if (result == 1)
	{
		free_env(env_with_new_var);
		return (NULL);
	}
	return (env_with_new_var);
}
