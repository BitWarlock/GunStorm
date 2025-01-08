/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:52:09 by mrezki            #+#    #+#             */
/*   Updated: 2023/12/22 11:26:45 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_new_token(size_t size)
{
	char	*str;

	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	return (str);
}

static int	ft_count_tokens(char const *s, char c)
{
	int	i;
	int	tokens;
	int	state;

	if (!s)
		return (0);
	state = 0;
	tokens = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			state = 0;
		else if (state == 0)
		{
			state = 1;
			++tokens;
		}
	}
	return (tokens);
}

static int	ft_token_len(char const *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] == c)
		i++;
	while (str[i] != c && str[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static char	**free_all(char **tokens, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		free(tokens[i]);
	free(tokens);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		tok_n;
	int		j;
	int		tok_len;
	char	**tokens;

	tokens = malloc(sizeof(char *) * (ft_count_tokens(s, c) + 1));
	if (!tokens)
		return (NULL);
	tok_n = -1;
	j = 0;
	while (++tok_n < ft_count_tokens(s, c))
	{
		tok_len = 0;
		tokens[tok_n] = ft_new_token(ft_token_len(&s[j], c));
		if (!(tokens[tok_n]))
			return (free_all(tokens, tok_n));
		while (s[j] == c)
			j++;
		while (s[j] != c && s[j])
			tokens[tok_n][tok_len++] = s[j++];
		tokens[tok_n][tok_len] = '\0';
	}
	tokens[tok_n] = NULL;
	return (tokens);
}
// {
//     char	**tokens;
//     tokens = ft_split("--229-abc----229a2ac0-846b-11ee-b0f1-6798e89--", '-');
//
// 	int	i = 0;
//     for (i = 0; tokens[i] != NULL; i++)
//     {
//         printf("%s\n", tokens[i]);
// 		free(tokens[i]);
//     }
//
//     return EXIT_SUCCESS;
// }
