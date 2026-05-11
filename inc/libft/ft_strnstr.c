/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:31:43 by acarbajo          #+#    #+#             */
/*   Updated: 2025/04/23 22:57:14 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		d;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		d = 0;
		while (((i + d) < len) && (big[i + d] == little[d])
			&& (big[i + d] != '\0'))
			d++;
		if (little[d] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
