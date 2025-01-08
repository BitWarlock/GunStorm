/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 06:32:48 by mrezki            #+#    #+#             */
/*   Updated: 2024/02/17 14:47:39 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digit(int i)
{
	unsigned int	a;
	unsigned int	b;

	a = 0;
	if (i < 0)
		b = i * -1;
	else
		b = i;
	while (b != 0)
	{
		b /= 10;
		a++;
	}
	return (a);
}

int	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	int		count;

	count = count_digit(n);
	nb = n;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb *= -1;
	}
	if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
		ft_putchar_fd(nb % 10 + '0', fd);
	return (count);
}
