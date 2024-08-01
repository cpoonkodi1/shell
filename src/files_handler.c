/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 07:53:01 by olmohame          #+#    #+#             */
/*   Updated: 2024/07/26 06:42:11 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prep_msg(t_shell **shell, char *str, char *cmd, char *err)
{
	size_t	len;
	char	*const_msg;

	len = ft_strlen(str) + ft_strlen(cmd) + ft_strlen(err);
	const_msg = (char *)ft_calloc((len + 1), sizeof(char));
	if (!const_msg)
		exit(exit_msg(shell, "Malloc failed.\n", 0, EXIT_FAILURE));
	ft_strcpy(const_msg, str);
	ft_strcpy(const_msg + ft_strlen(str), cmd);
	ft_strcpy(const_msg + ft_strlen(str) + ft_strlen(cmd), err);
	return (const_msg);
}

int	validate_infile(t_shell **shell, char *file, int *syn_err)
{
	char	*err_str;
	int		fd;
	int		oflag;

	oflag = O_RDONLY;
	fd = open(file, oflag);
	if (fd == -1)
	{
		*syn_err = 2;
		err_str = prep_msg(shell, "minishell: ", file, "");
		perror(err_str);
		free(err_str);
		err_str = NULL;
	}
	return (fd);
}

int	validate_outfile(t_shell **shell, char *file, int append, int *syn_err)
{
	char	*err_str;
	int		fd;
	int		oflag;

	oflag = O_WRONLY | O_CREAT | O_TRUNC;
	if (append)
		oflag = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(file, oflag, 0644);
	if (fd == -1)
	{
		*syn_err = 2;
		err_str = prep_msg(shell, "minishell: ", file, "");
		perror(err_str);
		free(err_str);
		err_str = NULL;
	}
	return (fd);
}
