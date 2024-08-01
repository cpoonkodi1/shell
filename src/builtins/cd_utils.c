/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:32:36 by pchennia          #+#    #+#             */
/*   Updated: 2024/07/31 11:03:54 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*arg_err_msg(char *pre, char *str, char *cmd, t_shell *mshell)
{
	size_t	len;
	char	*error_message;

	len = ft_strlen(pre) + ft_strlen(cmd) + ft_strlen(str) + 1;
	error_message = (char *)malloc(len);
	if (error_message == NULL)
		exit(exit_msg(&mshell, "Malloc failed.\n", 0, EXIT_FAILURE));
	bi_strcpy(error_message, pre);
	ft_strcat(error_message, cmd);
	ft_strcat(error_message, str);
	return (error_message);
}

void	check_arg_two(t_shell *mshell, t_sub *subs)
{
	char	*msg;
	int		fd;

	fd = 1;
	if (ft_strcmp(subs->cmd_arr[2], "2") == 0)
	{
		if (subs->fd_out > 0)
			fd = subs->fd_out;
		msg = arg_err_msg(CD, NO_FILE, subs->cmd_arr[1], mshell);
		ft_putstr_fd(msg, fd);
		free(msg);
	}
	else if (!check_isdigit(subs->cmd_arr[2])
		&& ft_atoi(subs->cmd_arr[2]) > 1023)
	{
		error_msg(CD, BAD_FD, subs->cmd_arr[1], mshell);
	}
	else
		error_msg(CD, NO_FILE, subs->cmd_arr[1], mshell);
	mshell->execution_status = 1;
}

int	check_isdigit(char *str)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (str[i] != 0)
	{
		if (!ft_isdigit(str[i]))
		{
			found = 1;
			break ;
		}
		i++;
	}
	return (found);
}

void	print_err(char *part_one, char *part_two, char *part_three)
{
	ft_putstr_fd(part_one, STDERR_FILENO);
	ft_putstr_fd(part_two, STDERR_FILENO);
	ft_putstr_fd(part_three, STDERR_FILENO);
}

int	is_dir(const char *name)
{
	DIR	*dir;

	dir = opendir(name);
	if (dir)
	{
		closedir(dir);
		return (0);
	}
	if (errno == ENOTDIR)
		return (1);
	return (-1);
}
