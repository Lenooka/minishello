/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 23:27:16 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/02 14:32:53 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	unclosed_quote(char *inp)
{
	int		i;
	char	c;

	i = 0;
	while (inp[i] != '\0' && inp != NULL)
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

int	quote_syntax(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str && str[i])
	{
		if (parser_op(str[i]) == 3)
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (!str[i])
			{
				write(2, "MiniShell: syntax error: unclosed quote marks\n", 46);
				return (1);
			}
		}
		if (str[i])
			i++;
	}
	return (0);
}

int	start_syntax(char *inp)
{
	
}

int	end_syntax(char *input)
{

}

int	pipe_syntax(char *input)
{
	
}
int	dollar_syntax(char *input)
{
	
}