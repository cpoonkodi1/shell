/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:13:18 by pchennia          #+#    #+#             */
/*   Updated: 2024/07/26 08:22:38 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_global_var(t_shell *mshell)
{
	if (g_signal_status != 0)
	{
		if (g_signal_status == SIGINT)
			mshell->execution_status = 130;
		else if (g_signal_status == SIGQUIT)
			mshell->execution_status = 131;
		g_signal_status = 0;
	}
}

void	update_termios(int set_echoctl)
{
	struct termios	info;

	ft_bzero(&info, sizeof(struct termios));
	if (set_echoctl == 1)
	{
		tcgetattr(0, &info);
		info.c_lflag |= ECHOCTL;
		tcsetattr(0, TCSANOW, &info);
	}
	else
	{
		tcgetattr(0, &info);
		info.c_lflag &= ~ECHOCTL;
		tcsetattr(0, TCSANOW, &info);
	}
}
