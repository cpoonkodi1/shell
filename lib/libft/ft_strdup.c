/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 04:27:10 by olmohame          #+#    #+#             */
/*   Updated: 2023/11/15 02:58:49 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t		src_len;
	char		*replica;
	size_t		i;

	i = 0;
	src_len = ft_strlen(src);
	replica = (char *)malloc((src_len + 1) * sizeof(char));
	if (replica == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		replica[i] = src[i];
		i++;
	}
	replica[i] = '\0';
	return (replica);
}
