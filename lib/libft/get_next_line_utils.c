/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 05:36:00 by olmohame          #+#    #+#             */
/*   Updated: 2023/11/22 14:59:16 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*gnl_memset(void *ptr, int c, size_t len)
{
	unsigned char	*p;

	p = (unsigned char *)ptr;
	while (len-- > 0)
	{
		*p = (unsigned char)c;
		p++;
	}
	return (ptr);
}

static void	*gnl_calloc(size_t nitems, size_t size)
{
	void	*res;
	int		n_bytes;

	if (nitems != 0 && size > SIZE_MAX / nitems)
		return (0);
	n_bytes = nitems * size;
	res = malloc(n_bytes);
	if (res == NULL)
	{
		return (NULL);
	}
	gnl_memset(res, 0, n_bytes);
	return (res);
}

static char	*gnl_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	dest_len;

	i = 0;
	dest_len = gnl_strclen(dest, '\0');
	while (src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}

char	*gnl_strndup(const char *src, size_t len)
{
	unsigned int	src_len;
	char			*replica;
	unsigned int	i;

	i = 0;
	src_len = gnl_strclen(src, '\0');
	if (len > src_len)
		len = src_len;
	replica = (char *)malloc((len + 1) * sizeof(char));
	if (replica == NULL)
	{
		return (NULL);
	}
	while (src[i] && i < len)
	{
		replica[i] = src[i];
		i++;
	}
	replica[i] = '\0';
	return (replica);
}

char	*gnl_strjoin(const char *s1, const char *s2)
{
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (gnl_strndup(s2, gnl_strclen(s2, '\0')));
	if (!s2)
		return (gnl_strndup(s1, gnl_strclen(s1, '\0')));
	res = (char *)gnl_calloc(\
			(gnl_strclen(s1, '\0') + gnl_strclen(s2, '\0') + 1), sizeof(char));
	if (!res)
	{
		return (NULL);
	}
	gnl_strcat(res, s1);
	gnl_strcat(res, s2);
	return (res);
}
