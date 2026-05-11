/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:31:43 by acarbajo          #+#    #+#             */
/*   Updated: 2025/04/23 22:57:06 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t s)
{
	size_t	i;
	size_t	d;

	i = 0;
	while (src[i] != '\0')
		i++;
	if (s == 0)
		return (i);
	d = 0;
	while ((d < (s - 1)) && (src[d] != '\0'))
	{
		dest[d] = src[d];
		d++;
	}
	dest[d] = '\0';
	return (i);
}
