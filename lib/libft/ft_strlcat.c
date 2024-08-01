/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 03:05:17 by olmohame          #+#    #+#             */
/*   Updated: 2023/11/17 15:58:48 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t buffer_size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	if (!dest && !buffer_size)
		return (ft_strlen(src));
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (buffer_size < (dest_len + 1))
		return (buffer_size + src_len);
	while (src[i] != '\0' && (dest_len + i + 1) < buffer_size)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
