/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 02:27:26 by olmohame          #+#    #+#             */
/*   Updated: 2023/11/17 15:59:25 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char c)
{
	return (c == '\f' || c == '\t' || c == '\r' || c == ' ' \
				|| c == '\v' || c == '\n');
}

static int	detect_flow(long num, int dig)
{
	if (num > LONG_MAX / 10)
		return (1);
	else if (num * 10 > (LONG_MAX - dig))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			track_sign;
	long long	num;

	i = 0;
	num = 0;
	track_sign = 1;
	while (ft_isspace(str[i]) && str[i])
		i++;
	if ((str[i] == '+' || str[i] == '-') && str[i])
	{
		if (str[i] == '-')
			track_sign = 0;
		i++;
	}
	while (ft_isdigit(str[i]) && str[i])
	{
		if (detect_flow(num, str[i] - '0'))
			return (-1 * track_sign);
		num = (num) * 10 + str[i] - '0';
		i++;
	}
	if (!track_sign)
		num *= -1;
	return (num);
}
