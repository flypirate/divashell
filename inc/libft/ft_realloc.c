/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albegar2 <albegar2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 20:25:54 by albegar2          #+#    #+#             */
/*   Updated: 2026/05/11 21:43:26 by albegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size, size_t old_size)
{
	char	*result;

	if (!ptr)
	{
		result = malloc(size);
		if (!result)
			return (NULL);
		return (result);
	}
	if (size == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}
	result = malloc(size);
	if (!result)
		return (NULL);
	ft_memmove(result, ptr, old_size);
	free(ptr);
	return (result);
}
