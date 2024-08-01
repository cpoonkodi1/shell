/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 05:26:56 by olmohame          #+#    #+#             */
/*   Updated: 2023/11/19 08:53:03 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	in(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;
	int	len;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	while (in(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (in(s1[end], set) && end > start - 1)
		end--;
	len = end - start + 1;
	return (ft_substr(s1, start, len));
}
