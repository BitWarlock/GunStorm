/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:25:01 by mrezki            #+#    #+#             */
/*   Updated: 2023/12/21 21:26:39 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if (!dst && !src)
		return (NULL);
	if (dst == src)
		return (dst);
	while (++i < n)
		*((char *)dst + i) = *((char *)src + i);
	return (dst);
}
//
// int main(void)
// {
// 	char	dst[] = "12345678910";
// 	ft_memmove(dst + 2, dst, 6);
// 	printf("%s\n", dst);
//
// 	return EXIT_SUCCESS;
// }
