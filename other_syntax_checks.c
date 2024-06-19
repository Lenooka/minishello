/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_syntax_checks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:54:23 by otolmach          #+#    #+#             */
/*   Updated: 2024/06/19 13:43:07 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir_syntax(char *input)
{
	int	x;
	int	len;

	x = 0;
	len = ft_strlen(input) - 1;
	while (x < len)
	{
		while (x < len && input[x] != '<'
			&& input[x] != '>' && !check_quotes(input, x))
			x++;
		if (x < len && check_quotes(input, x))
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
			&& input[x] != '>' && !check_quotes(input, x))
			x++;
		if (x < len && check_quotes(input, x))
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
			&& input[x] != '>' && !check_quotes(input, x))
			x++;
		if (x < len && check_quotes(input, x))
			x = little_skip_quotes(input, x, len);
		if (x < len && (input[x] == '>' || input[x] == '<'))
		{
			x++;
			if (x < len && check_space_tabs(input, x))
			{
				while (x < len && check_space_tabs(input, x))
					x++;
				if (input[x] && check_redir_pipe(input, x))
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
		if (x < len && check_quotes(input, x))
			x = little_skip_quotes(input, x, len);
		if (x < len && (input[x] == '&' || input[x] == '('
				|| input[x] == ')' || input[x] == ';'))
			return (input[x]);
		x++;
	}
	return (0);
}
