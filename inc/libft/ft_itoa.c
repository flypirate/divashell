/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:29:38 by acarbajo          #+#    #+#             */
/*   Updated: 2025/04/23 22:56:29 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_int_len(int n)
{
	int		len;
	long	nu;

	nu = (long)n;
	len = 1;
	if (nu < 0)
	{
		len++;
		nu = nu * -1;
	}
	while (nu >= 10)
	{
		nu = nu / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*num;
	int		len;
	int		i;
	long	nu;

	nu = (long)n;
	len = ft_int_len(n);
	num = malloc(len + 1);
	if (!num)
		return (NULL);
	i = 0;
	if (nu < 0)
	{
		num[i++] = '-';
		nu = nu * -1;
	}
	num[len--] = '\0';
	while (nu >= 10)
	{
		num[len--] = (nu % 10) + '0';
		nu = nu / 10;
	}
	num[len] = nu + '0';
	return (num);
}
