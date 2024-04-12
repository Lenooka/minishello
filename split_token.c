/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:53:11 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/12 21:28:06 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  quote == 1m / 3n
  redir&&pip == 2
  tab space == 3m / 1n
  $ = 4
*/


char	*split_tmp(t_mnshll *ms, char *str, int word_len)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	tmp = malloc(sizeof(char) * (word_len + 1));
	if (!tmp)
		ft_exit(ms);
	while (*str && i < word_len)
		tmp[i++] = *str++;
	tmp[i] = '\0';
	return (tmp);
}


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
			i = envar(str, i);
		else if (str[i] && !parser_codes(str[i]))
			i = space_tab(str, i);
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
		return (others(str, i)); 		//unfinished
	if (str[i] && parser_codes(str[i]) == 4)
		return (envar(str, i));
	if (str[i] && !parser_codes(str[i]))
		return (space_tab(str, i));
	return (i);
}

char	**split_tokenize(t_mnshll  *ms, char *str)
{
	int		i;
	int		word_len;
	char	**buff;
	int		ms_words;

	i = 0;
	ms_words = count_words(str);
	buff = malloc(sizeof(char *) * (ms_words + 1));
	if (!buff)
		ft_exit(ms);
	while (i < ms_words)
	{
		while (*str && parser_codes(*str) == 3)
			str++;
		word_len = ft_toklen(str);
		buff[i++] = split_tmp(ms, str, word_len);
		str = str + word_len;
	}
	buff[i] = 0;
	return (buff);
}
