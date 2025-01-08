/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:56:20 by mrezki            #+#    #+#             */
/*   Updated: 2023/12/22 10:23:12 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ito(int len, long n, int sign)
{
	char	*ptr;
	int		si;

	si = 0;
	if (!sign)
		si = 1;
	ptr = malloc(sizeof(char) * len + sign + 1);
	if (!ptr)
		return (NULL);
	ptr[len + sign] = '\0';
	while (len)
	{
		ptr[len - si] = n % 10 + '0';
		n /= 10;
		len--;
	}
	if (sign)
		ptr[0] = '-';
	return (ptr);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		len;
	int		sign;

	nb = n;
	sign = 0;
	if (nb < 0)
	{
		nb = -nb;
		sign = 1;
	}
	len = size(nb);
	return (ito(len, nb, sign));
}
//
// int main(void)
// {
// 	printf("%s\n", ft_itoa(2147483645648));
//
// 	return EXIT_SUCCESS;
// }
