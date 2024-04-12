/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/12 17:44:33 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	parser_codes(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	if (c == '<' || c == '>' || c == '|')
		return (2);
	if (c == ' ' || c == '\t')
		return (3);
	if (c == '$')
		return (4);
	return (0);
}


int	big_skip_quotes(char *str, char c, int x)
{
	if (str[x] && str[x] == c)
	{
		x++;
		while (str[x] && str[x] != c)
			x++;
		if (str[x] == '\0')
			return (x);
		x++;
		if (str[x] && !parser_codes(str[x]))
			return (space_tab(str, x))
		else if (str[x] && str[x] == '$')
			return (envar(str, x));
		else if (str[x] && parser_codes(str[x]) == 1)
			return (big_skip_quotes(str, str[x], x))
	}
	return (x);
}

int	space_tab(char *str, int x)
{
	if (str[x] && !parser_codes(str[x]))
	{
		while (str[x] && !parser_codes(str[x]))
			x++;
		if (str[x] && str[x] == '$')
			return (envar(str, x));
		else if (str[x] && parser_codes(str[x]) == 1)
			return (big_skip_quotes(str, str[x], x))
	}
	return (x);
}

int	envar(char *str, int x)
{
	if (str[x] == '$')
	{
		x++;
		if (str[x] && parser_codes(str[x]) == 1)
			return (big_skip_quotes(str, str[x], x));
		else if (str[x] && !parser_codes(str[x]))
			return (space_tab(str, x))
	}
	return (x);
}

int others(char *str, int x)
{
	if (str[x] && str[x] == '|')
		x++;
	else if (str[x] == '>')
	{
		x++;
		if (str[x] && (str[x] == '>' || str[x] == '|'))
			x++;
	}
	else if (str[x] == '<')
	{
		x++;
		if (str[x] && (str[x] == '<' || str[x] == '>'))
			x++;
	}
	return (x);
}
