/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 05:00:02 by olmohame          #+#    #+#             */
/*   Updated: 2023/11/16 04:08:34 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_membcpy(void *dst, const void *src, size_t n)
{
	char	*dst_str;
	char	*src_str;

	dst_str = (char *)dst;
	src_str = (char *)src;
	if (!dst_str && !src_str)
		return (0);
	while (n > 0)
	{
		n --;
		dst_str[n] = src_str[n];
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	if (n > 0)
	{
		if (src < dst && src + n > dst)
			ft_membcpy(dst, src, n);
		else
			ft_memcpy(dst, src, n);
	}
	return (dst);
}
