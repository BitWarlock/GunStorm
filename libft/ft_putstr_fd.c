/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 06:24:50 by mrezki            #+#    #+#             */
/*   Updated: 2024/02/17 14:33:11 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (s == NULL)
		s = "(null)";
	i = -1;
	while (s[++i])
		ft_putchar_fd(s[i], fd);
	return (i);
}
// #include <fcntl.h>
//
// int main(void)
// {
// 	int fd = open("test1.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
// 	if (fd < 0)
// 		perror("Fail");
// 	ft_putchar_fd('a', fd);
// 	ft_putnbr_fd(123456, fd);
// 	ft_putstr_fd("abcd\n", fd);
// 	ft_putendl_fd("abcd", fd);
//
// 	close(fd);
//
// 	return EXIT_SUCCESS;
// }
