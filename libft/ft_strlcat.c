/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 04:07:56 by mrezki            #+#    #+#             */
/*   Updated: 2023/12/22 10:36:07 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lendst;
	size_t	lensrc;
	size_t	i;

	if (dst == NULL && dstsize == 0)
		return (0);
	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	if (dstsize <= lendst || dstsize == 0)
		return (lensrc + dstsize);
	else
	{
		i = 0;
		while (src[i] && lendst + 1 + i < dstsize)
		{
			dst[lendst + i] = src[i];
			i++;
		}
		dst[lendst + i] = '\0';
	}
	return (lendst + lensrc);
}
//
// #include <string.h>
//
// int	main(void)
// {
// 	char	dst[11] = "abcdef";
// 	char	src[] = "1234";
// 	printf("Return: %zu\ndst:%s\nsrc:%s\n", strlcat(dst, src, 11), dst, src);
// }
