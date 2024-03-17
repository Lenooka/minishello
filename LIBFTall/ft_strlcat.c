/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:51:10 by otolmach          #+#    #+#             */
/*   Updated: 2023/09/05 15:51:12 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	c;

	c = 0;
	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (size == 0)
		return (size + slen);
	if (dlen < size - 1 && size > 0)
	{
		while (src[c] != '\0' && dlen + c < size - 1)
		{
			dst[dlen + c] = src[c];
			c++;
		}
		dst[dlen + c] = '\0';
	}
	if (dlen < size)
	{
		return (dlen + slen);
	}
	return (size + slen);
}
