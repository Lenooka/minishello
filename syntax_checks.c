/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 23:27:16 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/04 16:30:22 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	unclosed_quote(char *inp)
{
	int		i;
	char	c;

	i = 0;
	while (inp[i] != '\0')
	{
		if (parser_codes(inp[i]) == 1)
		{
			c = inp[i++];
			while (inp[i] != '\0' && inp[i] != c)
				i++;
			if (!inp[i])
				return (1);
		}
		if (inp[i] != '\0')
			i++;
	}
	return (0);
}
/*
int	parser_op(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	if (c == '<' || c == '>' || c == '|')
		return (2);
	if (c == '\'' || c == '\"')
		return (3);
	if (c == '$')
		return (4);
	return (0);
}
*/

int	start_syntax(char *input)
{
	int	x;

	x = 0;
	while (input[x] && parser_codes(input[x]) == 3)
		x++;
	if (str[x] == '|')
		return (1);
	return (0);
}

int	end_syntax(char *input)
{
	int	x;

	x = 0;
	while (input[x])
		x++;
	while (x >= 0)
	{
		if (input[x] == '|' || input[x] == '<' || input[x] == '>')
			return (1);
		else if (parser_codes(input[x]) == 3)
			x--;
		else
			break ;
	}
}	

int	pipe_syntax(char *input)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (str[x] && parser_codes(str[x]) == 1)
			x = skipping_quotes(str, str[x], x);
		else if (str[x] && str[x] == '|')
		{
			x++;
			while (str[x] && parser_codes(str[x]) == 3)
				x++;
			if (str[x] && str[x] == '|')
				return (1);
		}
		else
			x++;
	}
	return (0);
}

int	dollar_syntax(char *input)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (str[x] == '\'')
		{
			x++;
			while (str[x] && str[x] != '\'')
				x++;
			if (str[x] == '\0')
				break ;
			x++;
		}
		else if (str[x] == '$' && str[x + 1] == '$')
			return (1);
		else
			x++;
	}
	return (0);
}
