/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:53:11 by otolmach          #+#    #+#             */
/*   Updated: 2024/06/10 06:08:19 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(char *str)
{
	int	i;
	int	amm_words;

	i = 0;
	amm_words = 0;
	while (str && str[i])
	{
		while (str[i] && parser_codes(str[i]) == 3)
		{
			i++;
		}
		if (str[i] && parser_codes(str[i]) != 3)
		{
			amm_words++;
		}
		if (str[i] && parser_codes(str[i]) == 2)
			i = others(str, i);
		else if (str[i] && parser_codes(str[i]) == 1)
			i = big_skip_quotes(str, str[i], i);
		else if (str[i] && str[i] == '$')
			i = skip_envar(str, i);
		else if (str[i] && !parser_codes(str[i]))
			i = skip_spaces(str, i);
	}
	return (amm_words);
}

int	ft_toklen(char *str)
{
	int	i;

	i = 0;
	if (str[i] && parser_codes(str[i]) == 1)
		return (big_skip_quotes(str, str[i], i));
	if (str[i] && parser_codes(str[i]) == 2)
		return (others(str, i));
	if (str[i] && parser_codes(str[i]) == 4)
		return (skip_envar(str, i));
	if (str[i] && !parser_codes(str[i]))
		return (skip_spaces(str, i));
	return (i);
}

char	**split_tokenize(t_mnshll *minsh, char *str)
{
	char	**result;
	int		token_ammount;
	int		i;
	int		toklen;

	i = 0;
	token_ammount = count_words(str) + 1;
	result = (char **)malloc(sizeof(char *) * (token_ammount));
	if (!result)
		return (NULL);
	while (i < token_ammount - 1)
	{
		if (*str && parser_codes(*str) == 3)
			str++;
		else
		{
			toklen = ft_toklen(str);
			result[i++] = ft_strndup(minsh, str, toklen);
			if (!result[i - 1])
				return (free_arrays(result, i));
			str = str + toklen;
		}
	}
	result[i] = NULL;
	return (result);
}
