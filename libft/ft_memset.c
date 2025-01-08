/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 02:31:06 by mrezki            #+#    #+#             */
/*   Updated: 2023/12/22 11:26:40 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;

	p = (unsigned char *)b;
	while (len--)
		*p++ = (unsigned char)c;
	return (b);
}
//
// int main(void)
// {
// 	int a = 1;
//
// 	if (*(char *)&a == 1)
// 	{
// 		printf("little\n");
// 		ft_memset(&a, 255, 4);
// 		ft_memset(&a, 106, 1);
// 		printf("%d", a);
// 	}
//
// 	return EXIT_SUCCESS;
// }
