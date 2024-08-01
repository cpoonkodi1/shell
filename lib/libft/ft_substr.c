/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 04:25:10 by olmohame          #+#    #+#             */
/*   Updated: 2023/11/16 05:41:54 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strndup(const char *src, size_t len)
{
	unsigned int	src_len;
	char			*replica;
	unsigned int	i;

	i = 0;
	src_len = ft_strlen(src);
	if (len > src_len)
		len = src_len;
	replica = (char *)malloc((len + 1) * sizeof(char));
	if (replica == NULL)
		return (NULL);
	while (src[i] && i < len)
	{
		replica[i] = src[i];
		i++;
	}
	replica[i] = '\0';
	return (replica);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		len = 0;
		start = 0;
	}
	return (ft_strndup(s + start, len));
}
