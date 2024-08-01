/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 02:59:46 by olmohame          #+#    #+#             */
/*   Updated: 2024/07/04 23:14:34 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	dest_len;

	i = 0;
	dest_len = ft_strlen(dest);
	while (src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	res = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!res)
		return (NULL);
	ft_strcat(res, s1);
	ft_strcat(res, s2);
	return (res);
}

char	*ft_strsepjoin(char const *s1, char sep, char const *s2)
{
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	res = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 2, sizeof(char));
	if (!res)
		return (NULL);
	ft_strcat(res, s1);
	res[ft_strlen(s1)] = sep;
	ft_strcat(res, s2);
	return (res);
}
