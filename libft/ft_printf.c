/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:17:34 by mrezki            #+#    #+#             */
/*   Updated: 2024/02/17 14:36:14 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_flags(t_flags *flags)
{
	flags->space = 0;
	flags->hash = 0;
	flags->plus = 0;
}

static int	handle_specifier(char str, va_list *args, t_flags *flags)
{
	if (str == 'd' || str == 'i')
		return (print_number(va_arg(*args, int), flags));
	else if (str == 'x' || str == 'X')
		return (print_hex(va_arg(*args, unsigned int), flags, str));
	else if (str == 'c')
		return (ft_putchar_pf(va_arg(*args, int)));
	else if (str == 's')
		return (print_string(va_arg(*args, char *)));
	else if (str == 'p')
		return (print_address(va_arg(*args, void *)));
	else if (str == 'u')
		return (print_unsigned(va_arg(*args, unsigned int)));
	else if (str == '%')
		return (ft_putchar_pf('%'));
	else if (str)
		return (ft_putchar_pf(str));
	return (0);
}

static void	loop_string(va_list *args, const char *str, int *count)
{
	t_flags	flags;

	while (*str)
	{
		if (*str != '%')
		{
			*count += ft_putchar_pf(*str);
			str++;
		}
		else
		{
			init_flags(&flags);
			str++;
			while (check_flags(*str, &flags))
				str++;
			*count += handle_specifier(*str, args, &flags);
			if (*str)
				str++;
		}
	}
}

int	ft_printf(int fd, const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	if (write (1, "", 0) == -1)
		return (-1);
	if (fd == 1)
		loop_string(&args, format, &count);
	else
		loop_string_fd(&args, format, &count, fd);
	va_end(args);
	return (count);
}
