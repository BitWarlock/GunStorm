/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:41:29 by mrezki            #+#    #+#             */
/*   Updated: 2024/02/12 16:40:23 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*convert_base(unsigned long n, char c)
{
	char		*str;
	char		*tmp;
	static char	buffer[21];

	if (c == 'x')
		tmp = "0123456789abcdef";
	else if (c == 'X')
		tmp = "0123456789ABCDEF";
	str = &buffer[20];
	while (n)
	{
		*--str = tmp[n % 16];
		n /= 16;
	}
	return (str);
}

static int	print_lower(unsigned int n, t_flags *flags)
{
	int		count;
	char	*str;

	str = convert_base((unsigned int)n, 'x');
	count = 0;
	if (flags->hash == 1)
		count += ft_puts("0x");
	count += ft_puts(str);
	return (count);
}

static int	print_upper(unsigned int n, t_flags *flags)
{
	int		count;
	char	*str;

	str = convert_base((unsigned int)n, 'X');
	count = 0;
	if (flags->hash == 1)
		count += ft_puts("0X");
	count += ft_puts(str);
	return (count);
}

int	print_hex(unsigned int n, t_flags *flags, char c)
{
	if (n == 0)
		return (ft_putchar_pf('0'));
	if (c == 'x')
		return (print_lower(n, flags));
	return (print_upper(n, flags));
}

int	print_address(void *n)
{
	char	*str;
	int		count;

	count = 0;
	if (!n)
		return (ft_puts("0x0"));
	str = convert_base((unsigned long)n, 'x');
	count += ft_puts("0x");
	count += ft_puts(str);
	return (count);
}
