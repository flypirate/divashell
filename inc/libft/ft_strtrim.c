/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:13:22 by acarbajo          #+#    #+#             */
/*   Updated: 2026/04/22 22:42:38 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char s, char const *set)
{
	while (*set)
	{
		if (s == *set)
			return (1);
		set++;
	}
	return (0);
}

static unsigned int	upper_trim(char const *s1, char const *set)
{
	unsigned int	i;

	i = 0;
	while (is_set(*s1, set))
	{
		i++;
		s1++;
	}
	return (i);
}

static unsigned int	lower_trim(char const *s1, char const *set)
{
	unsigned int	i;

	i = ft_strlen(s1) - 1;
	while (i > 0 && is_set(s1[i], set))
		i--;
	return (i);
}

static char	*ft_emptystr(void)
{
	char	*trim;

	trim = (char *)malloc(sizeof(char) * 1);
	if (!trim)
		return (NULL);
	trim[0] = '\0';
	return (trim);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;
	char			*trim;
	unsigned int	i;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	start = upper_trim(s1, set);
	end = lower_trim(s1, set);
	if (start > end)
		return (ft_emptystr());
	trim = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!trim)
		return (NULL);
	while (start <= end)
	{
		trim[i] = s1[start];
		i++;
		start++;
	}
	trim[i] = '\0';
	return (trim);
}
