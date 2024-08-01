/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 03:10:37 by olmohame          #+#    #+#             */
/*   Updated: 2023/11/15 03:10:40 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int b, int fd)
{
	if (b == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(21474, fd);
		ft_putnbr_fd(83648, fd);
	}
	else
	{
		if (b < 0)
		{
			ft_putchar_fd('-', fd);
			b = b * -1;
		}
		if (b < 10)
		{
			b = b + '0';
			ft_putchar_fd(b, fd);
		}
		else
		{
			ft_putnbr_fd(b / 10, fd);
			ft_putnbr_fd(b % 10, fd);
		}
	}
}
