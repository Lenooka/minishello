/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:05:44 by otolmach          #+#    #+#             */
/*   Updated: 2023/09/04 17:05:46 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dst;
	char		*sors;
	size_t		i;

	if (!((char *)dest) && !((char *)src))
		return (0);
	dst = (char *) dest;
	sors = (char *) src;
	i = 0;
	while (i < n)
	{
		dst[i] = sors[i];
		i++;
	}
	return (dest);
}
