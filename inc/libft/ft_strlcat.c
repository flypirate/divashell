/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:31:43 by acarbajo          #+#    #+#             */
/*   Updated: 2025/04/23 22:57:03 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t s)
{
	size_t	i;
	size_t	d;
	size_t	t;

	i = 0;
	while (src[i] != '\0')
		i++;
	d = 0;
	while (dest[d] != '\0')
		d++;
	if (s == 0)
		return (i);
	if (s <= d)
		return (i + s);
	t = 0;
	while (((d + t) < (s - 1)) && (src[t] != '\0'))
	{
		dest[d + t] = src[t];
		t++;
	}
	dest[d + t] = '\0';
	return (i + d);
}
