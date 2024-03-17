/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 21:50:42 by otolmach          #+#    #+#             */
/*   Updated: 2023/09/06 21:50:44 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;

	if (!s || start >= ft_strlen(s))
	{
		return (ft_strdup(""));
	}
	if (len > ft_strlen(s + start))
	{
		len = ft_strlen(s + start);
	}
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
	{
		return (NULL);
	}
	ft_strlcpy(result, s + start, len + 1);
	return (result);
}
