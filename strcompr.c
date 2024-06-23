/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcompr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:57:54 by jhuber            #+#    #+#             */
/*   Updated: 2024/06/23 20:19:38 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_un_chr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	spec_strcmp(char *s1, char *s2, char c)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]) && i < len_un_chr(s2, c) - 1)
		i++;
	if (i < ((int)ft_strlen(s1) - 1))
		return (1);
	return (s1[i] - s2[i]);
}

int	ft_strcmp(char *s1, char *s2)
{
	int		i;
	char	a;
	char	b;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	a = s1[i];
	b = s2[i];
	return (a - b);
}

char	*ft_strrepdup(char *str, int len)
{
	char	*res;

	res = malloc(sizeof(char) * len + 1);
	if (!res)
	{
		printf("Minishell: Malloc error!\n");
		return (NULL);
	}
	ft_strlcpy(res, str, len + 1);
	return (res);
}