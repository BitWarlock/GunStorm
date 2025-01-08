/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 05:47:21 by mrezki            #+#    #+#             */
/*   Updated: 2023/12/22 11:26:58 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	len2;

	if (haystack == NULL && len == 0)
		return (NULL);
	i = 0;
	len2 = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i] && i + len2 <= len)
	{
		if (ft_strncmp(haystack + i, needle, len2) == 0)
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
// #include <string.h>
//
// int main(void)
// {
// 	char	*hay = "foo bar war";
// 	
// 	char	*nee = "bar";
// 	char	*ptr = ft_strnstr(hay, nee, -1);
// 	printf("%s\n", ptr);
//
// 	return EXIT_SUCCESS;
// }
