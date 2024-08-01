/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 02:39:56 by olmohame          #+#    #+#             */
/*   Updated: 2024/07/12 05:33:21 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digitcount(int n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n / 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	fillstr(char *numstr, long num, int digits)
{
	if (num == 0)
		numstr[0] = '0' + num;
	else
	{
		while (num)
		{
			digits--;
			numstr[digits] = '0' + (num % 10);
			num /= 10;
		}
	}
}

char	*ft_itoa(int numm)
{
	int		digits;
	long	num;
	char	*numstr;

	num = numm;
	digits = ft_digitcount(num);
	numstr = (char *)malloc((digits + 1) * sizeof(char));
	if (!numstr)
		return (0);
	numstr[digits] = '\0';
	if (num < 0)
	{
		num *= -1;
		numstr[0] = '-';
	}
	fillstr(numstr, num, digits);
	return (numstr);
}
