/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 09:54:16 by olmohame          #+#    #+#             */
/*   Updated: 2024/08/01 07:43:04 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	del_pipe(t_pipe **pipe)
{
	if (*pipe)
	{
		if ((*pipe)->pids)
		{
			free((*pipe)->pids);
			(*pipe)->pids = NULL;
		}
		if ((*pipe)->cmd_paths)
		{
			ft_del((*pipe)->cmd_paths, (*pipe)->num_cmd);
			(*pipe)->cmd_paths = NULL;
		}
		if ((*pipe)->pipes)
		{
			del_gen((*pipe)->pipes, (*pipe)->num_cmd - 1);
			(*pipe)->pipes = NULL;
		}
		free(*pipe);
		*pipe = NULL;
		return (0);
	}
	return (1);
}

int	reset_shell(t_shell **shell)
{
	if (shell && *shell)
	{
		close_pipes((*shell)->st_pipe, 0, 2);
		close_files(&(*shell)->subs, (*shell)->unlink_file, 2);
		lstclear(&(*shell)->subs);
		(*shell)->subs = NULL;
		del_pipe(&(*shell)->st_pipe);
		(*shell)->st_pipe = NULL;
		(*shell)->num_temp = 0;
		return (0);
	}
	return (1);
}

static int	del_shell(t_shell **shell)
{
	if (shell && *shell)
	{
		reset_shell(shell);
		if ((*shell)->curr_envp)
		{
			free_env((*shell)->curr_envp);
			(*shell)->curr_envp = NULL;
		}
		if ((*shell)->declare_env)
		{
			free_env((*shell)->declare_env);
			(*shell)->declare_env = NULL;
		}
		if ((*shell)->the_prompt)
		{
			free((*shell)->the_prompt);
			(*shell)->the_prompt = NULL;
		}
		free(*shell);
		*shell = NULL;
		return (0);
	}
	return (1);
}

int	exit_msg(t_shell **shell, char *str, int free_flag, int status)
{
	ssize_t	ret;

	ret = write (2, str, ft_strlen(str));
	if (free_flag)
	{
		free(str);
		str = NULL;
	}
	if (shell)
		del_shell(shell);
	if (ret == -1)
		exit(EXIT_FAILURE);
	return (status);
}

int	del_gen(int **mat, int num_fields)
{
	int	i;

	i = -1;
	if (mat)
	{
		while (++i < num_fields)
		{
			free(mat[i]);
			mat[i] = NULL;
		}
		free(mat);
		mat = NULL;
	}
	return (0);
}
