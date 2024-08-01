/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 07:32:06 by olmohame          #+#    #+#             */
/*   Updated: 2024/07/28 11:49:32 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_status = 0;

static t_shell	*new_shell(char **envp)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		exit(exit_msg(NULL, "Malloc failed.\n", 0, EXIT_FAILURE));
	shell->unlink_file = 1;
	shell->exit_code = 0;
	shell->should_exit = 0;
	shell->num_temp = 0;
	shell->doc_failed = 0;
	shell->delim_quoted = 0;
	shell->execution_status = 0;
	shell->subs = NULL;
	shell->st_pipe = NULL;
	shell->the_prompt = NULL;
	shell->homepath = getenv("HOME");
	shell->curr_envp = env_cpy(envp);
	shell->declare_env = env_cpy(envp);
	shell->the_prompt = get_prompt(envp);
	if (!(shell->the_prompt) || !(shell->curr_envp) || !(shell->declare_env))
		exit(exit_msg(&shell, "Malloc failed.\n", 0, EXIT_FAILURE));
	return (shell);
}

int	find_var(t_shell **mshell, char *key)
{
	int		i;
	char	*loc;

	i = -1;
	if (!(*mshell))
		exit(exit_msg(mshell, "Malloc failed.\n", 0, EXIT_FAILURE));
	if ((*mshell)->curr_envp)
	{
		while ((*mshell)->curr_envp[++i])
		{
			loc = ft_strnstr((*mshell)->curr_envp[i], key, ft_strlen(key));
			if (loc && (loc[ft_strlen(key)] != '='))
			{
				(*mshell)->st_pipe->path_name = \
							ft_strchr((*mshell)->curr_envp[i], '=') + 1;
				return (0);
			}
		}
	}
	(*mshell)->st_pipe->path_name = NULL;
	return (1);
}

static void	process_input(t_shell **mshell, char *buf)
{
	t_sub	*subs;
	long	ret;

	ret = build_subs(*mshell, buf);
	subs = (*mshell)->subs;
	if (ret == 0)
	{
		if (read_redirections(mshell, &subs) == 0)
		{
			creat_cmd_list(&subs, *mshell);
			new_pipe(mshell);
			if (g_signal_status == 0)
				executer(*mshell);
		}
	}
	else
		(*mshell)->execution_status = 2;
	reset_shell(mshell);
}

int	main(int argc, char **argv, char **envp)
{
	char	*buf;
	t_shell	*mshell;

	(void)argv;
	if (argc > 1)
		return (exit_msg(NULL, "Extra arguments.\n", 0, EXIT_FAILURE));
	mshell = new_shell(envp);
	while (1)
	{
		set_signal_main(mshell);
		buf = readline(mshell->the_prompt);
		if (!buf)
		{
			mshell->execution_status = 0;
			break ;
		}
		if (ft_strlen(buf) > 0)
			add_history(buf);
		if (ft_strlen(buf) && !spaces(buf))
			process_input(&mshell, buf);
		free(buf);
		if (mshell->should_exit)
			exit(exit_msg(&mshell, "", 0, mshell->execution_status));
	}
	exit(exit_msg(&mshell, "exit\n", 0, mshell->execution_status));
}
