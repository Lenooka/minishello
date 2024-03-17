/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:34:52 by otolmach          #+#    #+#             */
/*   Updated: 2023/09/06 16:34:53 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1 = s1;
	const unsigned char	*p2 = s2;
	size_t				i;

	i = 0;
	while (i < n)
	{
		if (p1[i] < p2[i])
		{
			return ((int)(p1[i] - p2[i]));
		}
		if (p1[i] > p2[i])
		{
			return ((int)(p1[i] - p2[i]));
		}
		i++;
	}
	return (0);
}
