/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:44:44 by mrezki            #+#    #+#             */
/*   Updated: 2024/02/12 17:22:36 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	locate(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

char	*ft_free(char **ptr)
{
	if (!(*ptr))
		return (NULL);
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

static void	init_vars(int *j, int *len, char *rest, char *buffer)
{
	int	len1;
	int	len2;

	*j = 0;
	if (!rest)
		len1 = 0;
	else
		len1 = ft_strlen(rest);
	if (!buffer)
		len2 = 0;
	else
		len2 = ft_strlen(buffer);
	*len = len1 + len2;
}

char	*strjoin(char *rest, char *buffer)
{
	char	*ptr;
	int		i;
	int		j;
	int		len;

	i = 0;
	if (!rest && !(*buffer))
		return (NULL);
	init_vars(&j, &len, rest, buffer);
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (ft_free(&rest));
	if (rest && *rest)
	{
		while (rest[i])
		{
			ptr[i] = rest[i];
			i++;
		}
	}
	while (buffer[j])
		ptr[i++] = buffer[j++];
	ptr[len] = '\0';
	free (rest);
	return (ptr);
}
