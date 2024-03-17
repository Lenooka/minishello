/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:03:20 by otolmach          #+#    #+#             */
/*   Updated: 2024/03/11 16:03:39 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

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

int main() 
{
    char *input;

    while (1) 
	{
        input = readline("Minishell <3 : ");
        if (!input)
            break;
        add_history(input);
        if (check_syntax(input) == 1)
        {
            printf("Invalid syntax\n");
            break ;
        }
        else
        {
            printf("%s\n", input);
            free(input);
        }
    }
	free(input);
    return (0);
}
