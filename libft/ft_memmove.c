/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 03:17:00 by mrezki            #+#    #+#             */
/*   Updated: 2023/11/07 03:58:36 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p;
	unsigned char	*s;

	p = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (p > s)
		while (len--)
			p[len] = s[len];
	else
		return (ft_memcpy(p, s, len));
	return (dst);
}
