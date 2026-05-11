/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:45:27 by acarbajo          #+#    #+#             */
/*   Updated: 2025/04/30 18:32:44 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char	**ft_alloc_split(char const *s, char c)
{
	char	**split;
	int		words;
	int		i;
	int		inword;

	i = 0;
	words = 0;
	inword = 0;
	while (s[i])
	{
		if (s[i] != c && inword == 0)
		{
			inword = 1;
			words++;
		}
		if (s[i] == c && inword == 1)
			inword = 0;
		i++;
	}
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	split[words] = NULL;
	return (split);
}

static void	free_loop(char **split, int w)
{
	while (w >= 0)
	{
		free(split[w]);
		w--;
	}
	free(split);
}

static char	**ft_setphrase(char const *s, char c, char **split, int w)
{
	size_t	start;
	size_t	end;
	size_t	i;

	end = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		end = i;
		if (end > start)
		{
			split[w] = ft_substr(s, (unsigned int)start, (size_t)end - start);
			if (!split[w])
				return (free_loop(split, w), NULL);
			w++;
		}
	}
	split[w] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s || !*s)
	{
		split = (char **)malloc(sizeof (char *) * 1);
		if (!split)
			return (NULL);
		split[0] = NULL;
		return (split);
	}
	split = ft_alloc_split(s, c);
	if (!split)
		return (NULL);
	split = ft_setphrase(s, c, split, 0);
	if (!split)
		return (NULL);
	return (split);
}
