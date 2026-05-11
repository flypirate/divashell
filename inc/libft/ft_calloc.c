/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:29:36 by acarbajo          #+#    #+#             */
/*   Updated: 2025/04/30 20:34:07 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

void	*ft_calloc(size_t num, size_t size)
{
	void			*ptr;
	unsigned char	*bytes;
	size_t			total;

	total = num * size;
	ptr = (char *) malloc(total);
	if (!ptr)
		return (NULL);
	bytes = (unsigned char *)ptr;
	while (total--)
	{
		*bytes = 0;
		bytes++;
	}
	return (ptr);
}
