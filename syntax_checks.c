/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 23:27:16 by otolmach          #+#    #+#             */
/*   Updated: 2024/03/28 15:53:50 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	unclosed_quote(char *inp)
{
	int		i;
	char	c;

	i = 0;
	while (inp[i] != '\0' && inp)
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