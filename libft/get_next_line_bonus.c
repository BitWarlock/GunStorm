/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:44:42 by mrezki            #+#    #+#             */
/*   Updated: 2024/02/12 17:18:58 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_read_buffer(int fd, char *rest)
{
	char	*buffer;
	int		check;

	buffer = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&rest));
	check = 1;
	while (!(locate(rest)))
	{
		check = read(fd, buffer, BUFFER_SIZE);
		if (check == 0)
			break ;
		if (check < 0)
		{
			ft_free(&rest);
			break ;
		}
		buffer[check] = '\0';
		rest = strjoin(rest, buffer);
	}
	free(buffer);
	return (rest);
}

static char	*ft_extract_line(char *rest)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!rest)
		return (NULL);
	while (rest[i] && rest[i] != '\n')
		i++;
	i += (rest[i] == '\n');
	tmp = malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (rest[i] && rest[i] != '\n')
	{
		tmp[i] = rest[i];
		i++;
	}
	if (rest[i] == '\n')
		tmp[i++] = '\n';
	tmp[i] = 0;
	return (tmp);
}

static char	*ft_get_rest(char *rest)
{
	char	*tmp;
	int		i;
	int		j;

	if (!rest)
		return (NULL);
	i = 0;
	j = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	i += (rest[i] == '\n');
	tmp = malloc((ft_strlen(rest) - i + 1));
	if (!tmp)
		return (ft_free(&rest));
	while (rest[i])
		tmp[j++] = rest[i++];
	tmp[j] = '\0';
	if (*tmp == 0)
		return (free(tmp), free(rest), NULL);
	ft_free(&rest);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*rest[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rest[fd] = ft_read_buffer(fd, rest[fd]);
	line = ft_extract_line(rest[fd]);
	if (!line)
		return (ft_free(&rest[fd]));
	rest[fd] = ft_get_rest(rest[fd]);
	return (line);
}
