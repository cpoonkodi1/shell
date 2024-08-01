/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:06:26 by pchennia          #+#    #+#             */
/*   Updated: 2024/07/28 15:06:58 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	signal_handler_main(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		g_signal_status = SIGINT;
	}
}

void	set_signal_main(t_shell *mshell)
{
	struct sigaction	sigact;

	update_termios(1);
	sigact.sa_handler = &signal_handler_main;
	sigact.sa_flags = 0;
	sigemptyset(&sigact.sa_mask);
	if (sigaction(SIGINT, &sigact, NULL) == -1)
	{
		perror("sigaction error");
		return ;
	}
	check_global_var(mshell);
	sigact.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sigact, NULL) == -1)
	{
		perror("sigaction error");
		return ;
	}
}

void	sig_handler_pipex_and_heredoc(int sig)
{
	if (sig == SIGQUIT)
	{
		g_signal_status = SIGQUIT;
		printf("Quit: 3\n");
	}
	else if (sig == SIGINT)
	{
		printf("\n");
		g_signal_status = SIGINT;
	}
}

int	status_for_signal(int sig_num)
{
	if (sig_num == SIGINT)
		return (130);
	else if (sig_num == SIGQUIT)
		return (131);
	else
		return (1);
}

void	set_signal_heredoc(void)
{
	struct sigaction	sigact;

	sigact.sa_handler = &sig_handler_pipex_and_heredoc;
	sigact.sa_flags = 0;
	sigemptyset(&sigact.sa_mask);
	if (sigaction(SIGINT, &sigact, NULL) == -1)
	{
		perror("sigaction error");
		return ;
	}
	update_termios(0);
	sigact.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sigact, NULL) == -1)
	{
		perror("sigaction error");
		return ;
	}
}
