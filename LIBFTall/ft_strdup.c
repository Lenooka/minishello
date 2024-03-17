/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:58:46 by otolmach          #+#    #+#             */
/*   Updated: 2024/01/06 13:42:50 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s)
{
	char	*cs;
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (s[size] != '\0')
	{
		size++;
	}
	cs = malloc(sizeof(char) * (size + 1));
	if (!cs)
	{
		return (NULL);
	}
	while (s[i])
	{
		cs[i] = s[i];
		i++;
	}
	cs[i] = '\0';
	return (cs);
}
