/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:27:01 by mrezki            #+#    #+#             */
/*   Updated: 2024/02/17 14:40:57 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_specifier_fd(char str, va_list *args, int fd)
{
	if (str == 'd' || str == 'i')
		return (ft_putnbr_fd(va_arg(*args, int), fd));
	else if (str == 'c')
		return (ft_putchar_fd(va_arg(*args, int), fd));
	else if (str == 's')
		return (ft_putstr_fd(va_arg(*args, char *), fd));
	else if (str == '%')
		return (ft_putchar_fd('%', fd));
	else if (str)
		return (ft_putchar_fd(str, fd));
	return (0);
}

void	loop_string_fd(va_list *args, const char *str, int *count, int fd)
{
	while (*str)
	{
		if (*str != '%')
		{
			*count += ft_putchar_fd(*str, fd);
			str++;
		}
		else
		{
			str++;
			*count += handle_specifier_fd(*str, args, fd);
			if (*str)
				str++;
		}
	}
}
