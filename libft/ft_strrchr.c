/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 05:04:31 by mrezki            #+#    #+#             */
/*   Updated: 2023/12/20 21:02:03 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*s;

	s = NULL;
	c = (char)c;
	while (*str)
	{
		if ((char)*str == c)
			s = (char *)str;
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return (s);
}
//
// int main(void)
// {
// 	char	*s = "123po 12 12 4563ab";
// 	printf("%s\n%s\n", ft_strchr(s, '3'), ft_strrchr(s, '3'));
//
// 	return EXIT_SUCCESS;
// }
