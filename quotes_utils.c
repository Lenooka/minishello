/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:57:54 by jhuber            #+#    #+#             */
/*   Updated: 2024/04/13 14:32:54 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	little_skip_quotes(char *str, int x, int len)
{
	char	c;

	c = str[x];
	x++;
	while (x < len && str[x] != c)
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
	while (str[i] != '\0')
	{
		if (parser_codes(str[i]) == 1)
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
