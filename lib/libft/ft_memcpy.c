/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 04:58:15 by olmohame          #+#    #+#             */
/*   Updated: 2023/11/13 05:09:38 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dststr;
	char	*srcstr;

	i = 0;
	dststr = (char *)dst;
	srcstr = (char *)src;
	if (!dststr && !srcstr)
		return (0);
	while (i < n)
	{
		dststr[i] = srcstr[i];
		i++;
	}
	return (dst);
}
