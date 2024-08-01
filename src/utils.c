/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 07:14:39 by olmohame          #+#    #+#             */
/*   Updated: 2024/07/26 15:59:39 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_elements(char **list_str)
{
	ssize_t	num_elem;

	num_elem = 0;
	while (list_str[num_elem])
		num_elem++;
	return (num_elem);
}

pid_t	do_waitpid(pid_t pid, int *wstatus, int options)
{
	pid_t	ret_pid;
	int		ret;

	ret_pid = waitpid(pid, wstatus, options);
	while (ret_pid == -1 && errno == EINTR)
	{
		if (pid >= 0)
		{
			ret = kill(pid, g_signal_status);
			g_signal_status = 0;
			if (ret < 0)
				printf("Unable to send signal. errno: %d", errno);
		}
		ret_pid = waitpid(pid, wstatus, options);
	}
	return (ret_pid);
}

void	process_exit_code(t_shell *mshell, int i)
{
	int	wait_status;
	int	sig_num;

	do_waitpid(mshell->st_pipe->pids[i], &wait_status, 0);
	if (WIFEXITED(wait_status))
		mshell->execution_status = WEXITSTATUS(wait_status);
	else if (WIFSIGNALED(wait_status))
	{
		sig_num = WTERMSIG(wait_status);
		mshell->execution_status = status_for_signal(sig_num);
	}
}

char	*here_doc_err(t_shell **shell, char *del)
{
	char	*temp;
	char	*full_msg;
	char	*length_str;

	length_str = ft_itoa(history_length);
	if (!length_str)
		exit(exit_msg(shell, "Malloc failed", 0, EXIT_FAILURE));
	temp = prep_msg(shell, "\nminishell: warning: here-document at line ", \
		length_str, " delimited by end-of-file (wanted `");
	free(length_str);
	full_msg = prep_msg(shell, temp, del, "\')\n");
	free(temp);
	return (full_msg);
}
