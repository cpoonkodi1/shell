/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 11:30:17 by pchennia          #+#    #+#             */
/*   Updated: 2024/07/31 11:06:01 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_equal(char *var, int *found)
{
	int	i;

	i = 0;
	*found = 0;
	while (var[i])
	{
		if (var[i] == '=')
		{
			*found = i;
			break ;
		}
		i++;
	}
	return (*found);
}

char	*ft_getcwd(char *var, char **env, char **path, t_shell *mshell)
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
			if (*path == NULL)
				exit(exit_msg(&mshell, "Malloc failed.\n", 0, EXIT_FAILURE));
			return (*path);
		}
		i++;
	}
	return (0);
}

void	display_pwd(t_shell *mshell)
{
	char	*cwd;
	char	*path;

	cwd = ft_getcwd("PWD=", mshell->curr_envp, &path, mshell);
	if (cwd == NULL)
	{
		cwd = getcwd(NULL, 0);
		if (cwd == NULL)
		{
			exit(exit_msg(&mshell, "Malloc failed.\n", 0, EXIT_FAILURE));
		}
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
}
