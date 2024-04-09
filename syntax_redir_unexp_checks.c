/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redir_unexp_checks.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:54:23 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/09 14:45:57 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//This logic can easily be overworked, re-think on how to handle every redirection check and check for the redirections.

int	redir_syntax(char *input)
{
    int x;
    int len;

    x = 0;
    len = ft_strlen(input) - 1;
    while (x < len)
    {
        while (x < len && input[x] != '<' && input[x] != '>' && parser_codes(input[x]) != 1)
            x++;
        if (x < len && parser_codes(input[x]) == 1)
        {
            while (++x < len && parser_codes(input[x]) != 1) //Inceasing x inside of a while statement, not sure if that works, it should but might not, we will see
                x++;
        }
        if (x < len && (input[x] == '>' && input[x + 1] == '<'))
            return (1);
        if (x < len && (input[x] == '<' && input[x + 1] == '>'))
            return (1);
        if (x < len && (input[x] == '<' && input[x + 1] == '|'))
            return (1);
        if (x < len && (input[x] == '>' && input[x + 1] == '|'))
            return (1);
        x++;
    }
    return (0);
}

int	double_redir_syntax(char *input)
{
    int x;
    int len;
    
    x = 0;
    len = ft_strlen(input) - 1;
    while (x < len)
    {
        while (x < len && input[x] != '<' && input[x] != '>' && parser_codes(input[x]) != 1)
            x++;
        if (x < len && parser_codes(input[x]) == 1)
            x = skipping_quotes(input, input[x], x);
        
    }
}

int	sucession_syntax(char *input)
{
	
}

int	token_syntax(char *input)
{
	
}