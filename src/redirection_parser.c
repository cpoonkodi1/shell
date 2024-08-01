/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 05:24:12 by olmohame          #+#    #+#             */
/*   Updated: 2024/07/28 12:12:05 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	sh_namelen(char *str, char *cond)
{
	size_t	str_len;

	str_len = 0;
	while (str[str_len] && \
				(!(in(str[str_len], cond) || ft_isspace(str[str_len])) \
													|| is_quoted(str, str_len)))
		str_len++;
	return (str_len);
}

static void	store_filename(t_shell **shell, \
				t_sub *sub, char *file_name, int *syn_err)
{
	if (sub->op % 2)
	{
		free(sub->fname_out);
		sub->fname_out = file_name;
		sub->op_out = sub->op;
		if (sub->fd_out != -1)
			close(sub->fd_out);
		if (sub->invalid_expansion != 1)
			sub->fd_out = \
			validate_outfile(shell, sub->fname_out, sub->op == 3, syn_err);
	}
	else
	{
		if (sub->op_in && sub->fname_in)
			unlink(sub->fname_in);
		free(sub->fname_in);
		sub->fname_in = file_name;
		sub->op_in = sub->op;
		if (sub->op)
			sub->fname_in = fill_doc(shell, file_name);
		if (sub->fd_in != -1)
			close(sub->fd_in);
		if (sub->invalid_expansion != 1 && (*shell)->doc_failed == 0)
			sub->fd_in = validate_infile(shell, sub->fname_in, syn_err);
	}
}

static ssize_t	handle_file(t_shell **shell, t_sub	*sub, \
										ssize_t ind, int *syn_err)
{
	char	*file;
	char	*msg;

	(*shell)->doc_failed = 0;
	ind++;
	while (ft_isspace(sub->str[ind]))
		ind++;
	file = ft_substr(sub->str, ind, sh_namelen(sub->str + ind, "<>"));
	if (!file)
		exit(exit_msg(shell, "Malloc failed.\n", 0, EXIT_FAILURE));
	ind += ft_strlen(file) - 1;
	(*shell)->delim_quoted = in('\'', file) + in('\"', file);
	msg = prep_msg(shell, "minishell: ", file, ": ambiguous redirect\n");
	expand_filename(shell, sub, &file);
	store_filename(shell, sub, file, syn_err);
	if ((*shell)->doc_failed)
		*syn_err = 2;
	if (sub->invalid_expansion)
	{
		*syn_err = 2;
		return (exit_msg(NULL, msg, 1, EXIT_FAILURE));
	}
	free(msg);
	return (ind);
}

static int	classify_op(t_shell **shell, t_sub	*sub, int *syn_err)
{
	ssize_t	i;
	ssize_t	j;

	i = -1;
	j = -1;
	while (sub->str[++i])
	{
		if (in(sub->str[i], "<>") && !is_quoted(sub->str, i))
		{
			sub->op = (sub->str[i] == '>');
			if (sub->str[i] == sub->str[i + 1])
			{
				sub->op += 2;
				i++;
			}
			i = handle_file(shell, sub, i, syn_err);
			if (*syn_err)
				return (*syn_err);
		}
		else
			sub->str[++j] = sub->str[i];
	}
	sub->str[++j] = 0;
	return (0);
}

int	read_redirections(t_shell **shell, t_sub **lst)
{
	t_sub	*temp;
	int		syn_err;

	if (lst && *lst)
	{
		syn_err = 0;
		temp = *lst;
		if (classify_op(shell, temp, &syn_err) == 1)
			return (1);
		while (temp->next != *lst)
		{
			syn_err = 0;
			temp = temp->next;
			if (classify_op(shell, temp, &syn_err) == 1)
				return (1);
		}
	}
	return (0);
}
