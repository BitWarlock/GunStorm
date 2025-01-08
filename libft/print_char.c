/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:37:22 by mrezki            #+#    #+#             */
/*   Updated: 2024/02/12 16:45:17 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_pf(char h)
{
	write (1, &h, 1);
	return (1);
}

int	ft_puts(char *str)
{
	int	count;

	count = -1;
	while (str[++count])
		ft_putchar_pf(str[count]);
	return (count);
}

int	print_string(char *str)
{
	if (!str)
		str = "(null)";
	return (ft_puts(str));
}
