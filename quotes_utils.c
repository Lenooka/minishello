/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:57:54 by jhuber            #+#    #+#             */
/*   Updated: 2024/05/03 12:11:30 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	little_skip_quotes(char *str, int x, int len)
{
	char	c;

	c = '\0';
	if (x < len && str[x])
        c = str[x];
	x++;
	while (x < len && str[x] != c && str[x] != '\0')
		x++;
	if (x < len)
		x++;
	return (x);
}

int	quote_amm(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (!str || !str[0])
		return (0);
	while (str[i] != '\0')
	{
		if (parser_codes(str[i]) == 1 && str[i])
		{
			i = little_skip_quotes(str, str[i], ft_strlen(str));
			n = n + 2;
		}
		else
			i++;
	}
	return (n);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		x;
	char	*temp;
	char	q;

	i = 0;
	x = 0;
	temp = ft_calloc(sizeof(char), (ft_strlen(str) - quote_amm(str) + 1));
	if (!temp)
		return (NULL);
	while (str[i])
	{
		if (parser_codes(str[i]) == 1)
		{
			q = str[i++];
			while (str[i] && str[i] != q)
				temp[x++] = str[i++];
			if (str[i])
				i++;
		}
		else
			temp[x++] = str[i++];
	}
	return (temp);
}

char	**rem_q_from_2d(char **array)
{
	int		i;
	char	**temp;

	i = 0;
	temp = ft_calloc(sizeof(char *), size_of_2d(array) + 1);
	if (!temp)
		return (NULL);
	while (array[i])
	{
		temp[i] = remove_quotes(array[i]);
		i++;
	}
	temp[i] = NULL;
	return (temp);
}
