/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 23:27:16 by otolmach          #+#    #+#             */
/*   Updated: 2024/06/10 06:31:45 by jhuber           ###   ########.fr       */
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

int	start_syntax(char *input)
{
	int	x;

	x = 0;
	while (input[x] && parser_codes(input[x]) == 3)
		x++;
	if (input[x] == '|')
		return (1);
	return (0);
}

int	end_syntax(char *input)
{
	int	x;

	x = 0;
	while (input[x])
		x++;
	x--;
	while (x >= 0)
	{
		if (input[x] == '|' || input[x] == '<' || input[x] == '>')
			return (1);
		else if (parser_codes(input[x]) == 3)
			x--;
		else
			break ;
	}
	return (0);
}

int	check_pipe_syntax(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (str[x] && parser_codes(str[x]) == 1)
			x = big_skip_quotes(str, str[x], x);
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

/* It works shut up
otolmach@c4r5p5:~$ echo "$HOME"
	/home/otolmach
otolmach@c4r5p5:~$ echo '$HOME'
	$HOME*/

int	check_dollar_syntax(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (check_squotes(str, x))
			break ;
		else if (str[x] == '$' && str[x + 1] == '$')
			return (1);
		else
			x++;
	}
	return (0);
}
