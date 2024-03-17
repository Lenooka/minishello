/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:00:56 by otolmach          #+#    #+#             */
/*   Updated: 2024/01/05 19:42:28 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*jstr;
	int		i;
	int		j;
	int		jlen;

	jlen = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	jstr = (char *)malloc(sizeof(char) * (jlen + 1));
	if (!jstr)
		return (NULL);
	while (*s1)
	{
		jstr[j] = *s1++;
		j++;
	}
	while (*s2)
	{
		jstr[j] = *s2++;
		j++;
		i++;
	}
	jstr[j] = '\0';
	return (jstr);
}
