/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redir_unexp_checks.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:54:23 by otolmach          #+#    #+#             */
/*   Updated: 2024/06/01 18:34:18 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_syntax(char *input)
{
	int	x;
	int	len;

	x = 0;
	len = ft_strlen(input) - 1;
	while (x < len)
	{
		while (x < len && input[x] != '<'
			&& input[x] != '>' && parser_codes(input[x]) != 1)
			x++;
		if (x < len && parser_codes(input[x]) == 1)
			x = little_skip_quotes(input, x, len);
		if (x < len && (input[x] == '>' && input[x + 1] == '<'))
			return (3);
		if (x < len && (input[x] == '<' && input[x + 1] == '>'))
			return (2);
		if (x < len && (input[x] == '<' && input[x + 1] == '|'))
			return (1);
		if (x < len && (input[x] == '>' && input[x + 1] == '|'))
			return (2);
		x++;
	}
	return (0);
}

int	double_redir_syntax(char *input)
{
	int	x;
	int	len;

	x = 0;
	len = ft_strlen(input) - 1;
	while (x < len)
	{
		while (x < len && input[x] != '<'
			&& input[x] != '>' && parser_codes(input[x]) != 1)
			x++;
		if (x < len && parser_codes(input[x]) == 1)
			x = little_skip_quotes(input, x, len);
		if (x < len && (input[x] == '>' || input[x] == '<'))
		{
			if (input[x + 1] == '>' || input[x + 1] == '<')
				x++;
			if (x < len && (input[x + 1] == '|'
					|| (input[x + 1] == ' ' && input[x + 2] == '|')))
				return (1);
		}
		x++;
	}
	return (0);
}

int	sucession_syntax(char *input, int len)
{
	int	x;

	x = 0;
	while (x < len)
	{
		while (x < len && input[x] != '<'
			&& input[x] != '>' && parser_codes(input[x]) != 1)
			x++;
		if (x < len && parser_codes(input[x]) == 1)
			x = little_skip_quotes(input, input[x], len);
		if (x < len && (input[x] == '>' || input[x] == '<'))
		{
			x++;
			if (x < len && parser_codes(input[x]) == 3)
			{
				while (x < len && parser_codes(input[x]) == 3)
					x++;
				if (input[x] && parser_codes(input[x]) == 2)
					return (1);
			}
		}
		x++;
	}
	return (0);
}

int	token_syntax(char *input)
{
	int	x;
	int	len;

	x = 0;
	len = ft_strlen(input);
	while (x < len && input[x])
	{
		if (x < len && parser_codes(input[x]) == 1)
			x = little_skip_quotes(input, x, len);
		if (x < len && (input[x] == '&' || input[x] == '('
				|| input[x] == ')' || input[x] == ';'))
			return (input[x]);
		x++;
	}
	return (0);
}
