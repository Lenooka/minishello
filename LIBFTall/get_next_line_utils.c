/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:06:55 by otolmach          #+#    #+#             */
/*   Updated: 2024/01/06 18:29:39 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_subline(char *s1)
{
	char	*result;
	int		i;

	i = 0;
	if (!s1[i])
		return (NULL);
	while (s1[i] && s1[i] != '\n')
		i++;
	result = malloc(sizeof(char) * (i + 2));
	if (!result)
		return (NULL);
	i = 0;
	while (s1[i] && s1[i] != '\n')
	{
		result[i] = s1[i];
		i++;
	}
	if (s1[i] == '\n')
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_sub_new_line(char *s1)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i] && s1[i] != '\n')
		i++;
	if (!s1[i])
	{
		free(s1);
		s1 = (NULL);
		return (NULL);
	}
	i++;
	while (s1[i])
		s1[j++] = s1[i++];
	s1[j] = '\0';
	return (s1);
}
