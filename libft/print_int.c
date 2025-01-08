/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:40:22 by mrezki            #+#    #+#             */
/*   Updated: 2024/02/12 16:40:51 by mrezki           ###   ########.fr       */
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

static void	put_nbr(int n)
{
	unsigned int	n1;

	if (n < 0)
	{
		ft_putchar_pf('-');
		n1 = -n;
	}
	else
		n1 = n;
	if (n1 / 10)
		put_nbr(n1 / 10);
	ft_putchar_pf((n1 % 10) + '0');
}

int	print_number(int n, t_flags *flags)
{
	int	count;

	count = count_digit(n);
	if (flags->space == 1 && flags->plus == 0 && n >= 0)
		count += ft_putchar_pf(' ');
	if (flags->plus == 1 && n >= 0)
		count += ft_putchar_pf('+');
	if (n <= 0)
		count++;
	put_nbr(n);
	return (count);
}

static char	*convert_dec(unsigned int n)
{
	char		*str;
	static char	buffer[21];

	if (!n)
		return ("0");
	str = &buffer[20];
	while (n)
	{
		*--str = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

int	print_unsigned(unsigned int n)
{
	char	*str;

	str = convert_dec(n);
	return (ft_puts(str));
}
