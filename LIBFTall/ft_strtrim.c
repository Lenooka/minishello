/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:02:56 by otolmach          #+#    #+#             */
/*   Updated: 2023/09/07 17:02:56 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	setdef(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
		{
			return (1);
		}
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ts;
	int		start;
	int		end;
	int		len;

	start = 0;
	while (s1[start] != '\0' && setdef(s1[start], set))
		start++;
	end = start;
	while (s1[end] != '\0')
		end++;
	while (end > start && setdef(s1[end - 1], set))
		end--;
	len = end - start;
	ts = (char *)malloc((sizeof(char)) * (len + 1));
	if (!ts)
		return (NULL);
	end = 0;
	while (end < len)
	{
		ts[end] = s1[start + end];
		end++;
	}
	ts[end] = '\0';
	return (ts);
}
