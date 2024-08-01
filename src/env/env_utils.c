/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 08:05:05 by pchennia          #+#    #+#             */
/*   Updated: 2024/07/31 11:02:04 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	if (i == 0)
		return (0);
	else
		return (1);
}

char	**env_cpy(char **env)
{
	int		i;
	char	**envcp;

	i = 0;
	while (env[i])
		i++;
	envcp = malloc(sizeof(char *) * (i + 1));
	if (!envcp)
		return (NULL);
	envcp[i] = NULL;
	i = 0;
	while (env[i])
	{
		envcp[i] = ft_strdup(env[i]);
		if (!envcp[i])
		{
			free_env(envcp);
			envcp = NULL;
			break ;
		}
		i++;
	}
	if (envcp)
		update_shlvl(envcp);
	return (envcp);
}

void	free_env(char **str)
{
	int	i;

	if (str)
	{
		i = 0;
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

/* 
	returns custom prompt with user or just std prompt if user is suppresed. 
	NULL if error
*/
char	*get_prompt(char **env)
{
	int		i;
	char	*user;
	char	*prompt;

	i = 0;
	user = NULL;
	while (env[i])
	{
		if (ft_strnstr(env[i], "USER=", 5))
		{
			user = ft_strjoin(D_BLUE, env[i] + 5);
			if (!user)
				return (NULL);
			break ;
		}
		i++;
	}
	if (user)
	{
		prompt = ft_strjoin(user, D_GREEN"@minishell "X);
		free(user);
	}
	else
		prompt = ft_strdup(D_GREEN"minishell "X);
	return (prompt);
}

// To print a variable with quotes around its value
void	print_variable_with_quotes(char *var)
{
	int	j;
	int	first_eq;

	j = 0;
	first_eq = 0;
	while (var[j])
	{
		write(STDERR_FILENO, &var[j], 1);
		if (var[j] == '=' && first_eq == 0)
		{
			first_eq = 1;
			write(STDERR_FILENO, "\"", 1);
		}
		j++;
	}
	ft_putendl_fd("\"", 1);
}
