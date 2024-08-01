/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 02:47:07 by olmohame          #+#    #+#             */
/*   Updated: 2023/11/15 03:11:12 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*res;
	int		n_bytes;

	n_bytes = nitems * size;
	if (nitems != 0 && n_bytes / nitems != size)
		return (0);
	res = malloc(n_bytes);
	if (res == NULL)
		return (NULL);
	ft_bzero(res, n_bytes);
	return (res);
}
