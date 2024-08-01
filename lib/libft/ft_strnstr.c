/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 03:14:43 by olmohame          #+#    #+#             */
/*   Updated: 2023/11/19 08:47:17 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *needle, size_t len)
{
	int		i;
	size_t	needle_len;
	size_t	str_len;

	i = 0;
	if (!str && !len)
		return (NULL);
	needle_len = ft_strlen(needle);
	str_len = ft_strlen(str);
	if (needle_len == 0)
		return ((char *)str);
	while (str[i] != '\0' && (i + needle_len <= str_len) \
			&& (i + needle_len <= len))
	{
		if (ft_strncmp(&str[i], needle, needle_len) == 0)
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}
