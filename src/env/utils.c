/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:24:02 by pchennia          #+#    #+#             */
/*   Updated: 2024/07/31 11:02:56 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	getcwd_err_msg(void)
{
	perror("cd: error retrieving current directory: ft_getcwd: cannot \
access parent directories");
}

void	prefix_with_msg(char *env_var, t_shell *shell, char *prefix)
{
	if (env_var == NULL)
	{
		free(prefix);
		exit(exit_msg(&shell, MF, 0, EXIT_FAILURE));
	}
}

void	free_prefix(char *prefix, char *value)
{
	if (prefix)
		free(prefix);
	if (value)
		free(value);
}

// returns 1 if found
int	found_in_env(char *var, char **env, char **path)
{
	int	i;
	int	foundeq;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], ft_strlen(var)) == 0)
		{
			find_equal(env[i], &foundeq);
			*path = ft_substr(env[i], foundeq + 1, ft_strlen(env[i]) - foundeq);
			return (1);
		}
		i++;
	}
	return (0);
}

void	bi_strcpy(char *dest, char *src)
{
	if (!dest || !src)
		return ;
	while (*src)
		*dest++ = *src++;
	*dest = 0;
}
