/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:03:20 by otolmach          #+#    #+#             */
/*   Updated: 2024/03/18 00:32:40 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

int check_syntax(char    *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] == '"')
        return (1);
        i++;
    }
    return (0);

}

int main(int arc, char **arv, char **env) 
{
    t_lexer	*lexer;
	
	lexer->input = NULL;
	arv = NULL;
	env = NULL;
	if (arc > 1)
		return (1);
    while (1) 
	{
        lexer->input = readline("Minishell <3 : ");
        if (lexer->input == NULL)
            break;
		if (ft_strlen(lexer->input) != 0)
        	add_history(lexer->input);
        if (check_syntax(lexer->input) == 1)
        {
            printf("Invalid syntax\n");
            break ;
        }
        else
        {
            printf("%s\n", lexer->input);
            free(lexer->input);
        }
    }
	free(lexer->input);
    return (0);
}
