/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 05:52:27 by mrezki            #+#    #+#             */
/*   Updated: 2023/12/21 16:48:48 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long	res;
	unsigned long	tmp;
	int				sign;

	tmp = 0;
	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		sign = ',' - *(str++);
	while (*str >= '0' && *str <= '9')
	{
		tmp = res * 10 + (*str - '0');
		if (res > tmp && sign == 1)
			return (-1);
		else if (res > tmp && sign == -1)
			return (0);
		res = tmp;
		str++;
	}
	return (sign * res);
}
//
// int main(void)
// {
// 	printf("%d\n", atoi("123456789123456789123456"));
// 	printf("%d\n", ft_atoi("123456789123456789123456"));
//
// 	return EXIT_SUCCESS;
// }
