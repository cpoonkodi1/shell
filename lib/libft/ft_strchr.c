/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 03:05:51 by olmohame          #+#    #+#             */
/*   Updated: 2024/07/12 05:35:25 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *str, int ca)
{
	unsigned char	c;
	char			*strcasted;

	c = (unsigned char)ca;
	strcasted = (char *)str;
	while (*strcasted || c == '\0')
	{
		if (*strcasted == c)
			return ((char *)strcasted);
		strcasted++;
	}
	return (0);
}
