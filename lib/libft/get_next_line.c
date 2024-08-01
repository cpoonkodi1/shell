/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 05:15:29 by olmohame          #+#    #+#             */
/*   Updated: 2024/07/15 06:36:18 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_strclen(const char *str, char cond)
{
	size_t	str_len;

	str_len = 0;
	while (str[str_len] != cond && str[str_len])
		str_len++;
	return (str_len);
}

char	*gnl_clean_up(char **str, char **str2)
{
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
	if (*str2 != NULL)
	{
		free(*str2);
		*str2 = NULL;
	}
	return (NULL);
}

static int	gnl_in(char c, const char *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

static char	*extract_line(char **board, int inc)
{
	char	cond;
	char	*line;
	char	*tmp;
	size_t	line_len;

	cond = '\n';
	line_len = gnl_strclen(*board, cond) + 1;
	line = gnl_strndup(*board, line_len - inc);
	if (gnl_strclen(*board, '\0') > line_len)
	{
		tmp = gnl_strndup(*board + line_len, gnl_strclen(*board, '\0'));
		gnl_clean_up(board, board);
		*board = tmp;
	}
	else
	{
		gnl_clean_up(board, board);
	}
	if (!line)
		return (gnl_clean_up(board, board));
	return (line);
}

char	*get_next_line(int fd, int inc)
{
	char		*buff;
	char		*tmp;
	static char	*board[MAX_FD];
	int			nbr;

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (gnl_clean_up(&board[fd], &board[fd]));
	nbr = 1;
	while (!nbr || !board[fd] || (!gnl_in('\n', board[fd]) && nbr))
	{
		gnl_memset(buff, 0, BUFFER_SIZE + 1);
		nbr = read(fd, buff, BUFFER_SIZE);
		if (nbr == -1 || (!nbr && !board[fd]))
			return (gnl_clean_up(&board[fd], &buff));
		tmp = gnl_strjoin(board[fd], buff);
		if (!tmp)
			return (gnl_clean_up(&board[fd], &buff));
		gnl_clean_up(&board[fd], &board[fd]);
		board[fd] = tmp;
	}
	gnl_clean_up(&buff, &buff);
	return (extract_line(&board[fd], inc));
}
