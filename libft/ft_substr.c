/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 06:54:32 by mrezki            #+#    #+#             */
/*   Updated: 2023/12/22 10:42:59 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	i = ft_strlen(s) - start;
	if (i > len)
		i = len;
	ptr = malloc(sizeof(char) * i + 1);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s + start, i + 1);
	return (ptr);
}
