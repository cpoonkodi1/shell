/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:31:32 by olmohame          #+#    #+#             */
/*   Updated: 2024/07/23 06:36:25 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	sh_strclen(char *str)
{
	size_t	str_len;

	str_len = 0;
	while (str[str_len] && \
		(!ft_isspace(str[str_len]) || is_quoted(str, str_len)))
		str_len++;
	return (str_len);
}

void	sh_del(char **strings_arr, ssize_t num_strings)
{
	ssize_t	i;

	i = -1;
	if (strings_arr)
	{
		while (++i < num_strings)
		{
			free(strings_arr[i]);
			strings_arr[i] = NULL;
		}
		free(strings_arr);
		strings_arr = NULL;
	}
}

size_t	sh_count(char *str)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (!*str)
			break ;
		str += sh_strclen(str);
		count++;
	}
	return (count);
}

static char	**sh_fill(char **strings_arr, char *str)
{
	ssize_t	index_w;
	ssize_t	num_words;

	index_w = 0;
	num_words = sh_count(str);
	while (index_w < num_words)
	{
		while (str && ft_isspace(*str))
			str++;
		strings_arr[index_w] = ft_substr(str, 0, sh_strclen(str));
		if (!strings_arr[index_w])
		{
			sh_del(strings_arr, index_w);
			return (NULL);
		}
		str += sh_strclen(str);
		index_w++;
	}
	strings_arr[num_words] = NULL;
	return (strings_arr);
}

char	**sh_split(char *str)
{
	char	**strings_arr;
	size_t	num_words;

	if (!str)
		return (NULL);
	num_words = sh_count(str);
	strings_arr = malloc((num_words + 1) * sizeof(char *));
	if (!strings_arr)
		return (NULL);
	strings_arr = sh_fill(strings_arr, str);
	return (strings_arr);
}
