/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 02:26:38 by olmohame          #+#    #+#             */
/*   Updated: 2023/11/15 02:26:47 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strclen(const char *str, char cond)
{
	size_t	str_len;

	str_len = 0;
	while (str[str_len] != cond && str[str_len])
		str_len++;
	return (str_len);
}

void	ft_del(char **strings_arr, size_t num_strings)
{
	size_t	i;

	i = -1;
	while (++i < num_strings)
		free(strings_arr[i]);
	free(strings_arr);
}

size_t	ft_count(char const *str, char sep)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		while (*str && *str == sep)
			str++;
		if (!*str)
			break ;
		str += ft_strclen(str, sep);
		count++;
	}
	return (count);
}

static char	**ft_fill(char **strings_arr, char const *str, char sep)
{
	size_t	index_w;
	size_t	num_words;

	index_w = 0;
	num_words = ft_count(str, sep);
	while (index_w < num_words)
	{
		while (str && *str == sep)
			str++;
		strings_arr[index_w] = ft_substr(str, 0, ft_strclen(str, sep));
		if (!strings_arr[index_w])
		{
			ft_del(strings_arr, index_w);
			return (NULL);
		}
		str += ft_strclen(str, sep);
		index_w++;
	}
	strings_arr[num_words] = NULL;
	return (strings_arr);
}

char	**ft_split(char const *str, char sep)
{
	char	**strings_arr;
	size_t	num_words;

	if (!str)
		return (NULL);
	num_words = ft_count(str, sep);
	strings_arr = malloc((num_words + 1) * sizeof(char *));
	if (!strings_arr)
		return (NULL);
	strings_arr = ft_fill(strings_arr, str, sep);
	return (strings_arr);
}
