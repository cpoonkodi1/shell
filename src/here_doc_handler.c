/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 09:50:03 by olmohame          #+#    #+#             */
/*   Updated: 2024/07/28 12:11:39 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*prompt_input(t_shell **shell, char *file, int temp_fd)
{
	if (write(STDOUT_FILENO, "> ", ft_strlen("> ")) == -1)
	{
		perror("minishell: here-document");
		free(file);
		file = NULL;
		close(temp_fd);
		exit(exit_msg(shell, "", 0, EXIT_FAILURE));
	}
	return (get_next_line(STDIN_FILENO, 0));
}

static int	not_delimiter(char *doc_delimiter, char *line)
{
	int	comp_len;

	comp_len = ft_strlen(line);
	if (ft_strncmp(line, doc_delimiter, comp_len) == '\n')
		return (0);
	return (1);
}

static void	write_to_doc(t_shell **shell, char *file, char *del, int temp_fd)
{
	char	*line;
	t_sub	sub;

	set_signal_heredoc();
	line = prompt_input(shell, file, temp_fd);
	while (line && not_delimiter(del, line))
	{
		if (!(*shell)->delim_quoted)
			expand_and_clean(&line, 1, &sub, *shell);
		if (write(temp_fd, line, ft_strlen(line)) == -1)
		{
			perror("minishell: here-document: write");
			(*shell)->doc_failed = 1;
			break ;
		}
		free(line);
		line = prompt_input(shell, file, temp_fd);
	}
	if (!line && g_signal_status != SIGINT)
		exit_msg(NULL, here_doc_err(shell, del), 1, 1);
	free(line);
}

static char	*gen_file_name(t_shell **shell)
{
	char	*ext;
	char	*filename;

	while (1)
	{
		ext = ft_itoa((*shell)->num_temp++);
		if (!ext)
			exit(exit_msg(shell, "Malloc failed", 0, EXIT_FAILURE));
		filename = ft_strjoin(".temp_mini_", ext);
		free(ext);
		if (!filename)
			exit(exit_msg(shell, "Malloc failed", 0, EXIT_FAILURE));
		if (access(filename, F_OK) != 0 || ((*shell)->num_temp + 1 == SIZE_MAX))
			break ;
		free(filename);
	}
	return (filename);
}

char	*fill_doc(t_shell **shell, char *delim)
{
	int		temp_fd;
	char	*new_file;

	new_file = NULL;
	(*shell)->doc_failed = 0;
	if (delim)
	{
		new_file = gen_file_name(shell);
		temp_fd = open(new_file, O_WRONLY | O_CREAT, 0644);
		if (temp_fd == -1)
		{
			perror("minishell: here-document");
			free(delim);
			delim = NULL;
			(*shell)->doc_failed = 1;
			return (new_file);
		}
		write_to_doc(shell, new_file, delim, temp_fd);
		close(temp_fd);
		free(delim);
		delim = NULL;
	}
	return (new_file);
}
