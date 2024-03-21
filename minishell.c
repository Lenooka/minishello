/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:03:20 by otolmach          #+#    #+#             */
/*   Updated: 2024/03/21 19:23:43 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_com_pos(char **com_array, int	pos)
{
	//find position untill "|"
}
//AAAAA
void    start_procces(t_mnshll *mnshll)
{
    int     com_run;
    int     pipefd[2];
    pid_t   pid;
    int     position;

    com_run = 0;
	position = 0;
    while (com_run < mnshll->command_amount) //the amount of the commands from parser
    {
		if (pipe(pipefd) == -1)
		{
			//free_error
		}
		pid = fork();
		if (pid < 0)
			//free_error
		if (pid == 0)
			position = 0;
			//child
		else
			position = 0;
            //parent
		position = find_com_pos(mnshll->com_array, position);
    }
}


int main(int arc, char **arv, char **env) 
{
    t_lexer	*lexer;
    t_mnshll    *mnshll;
	
	lexer->input = NULL;
	arv = NULL;
	env = NULL;
	if (arc > 1)
		return (1);
	if (!env || env[0][0] == '\0')
		//error handle
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
        else //init and syntax)
        {
            start_procces(mnshll);
            free(lexer->input);
        }
    }
	free(lexer->input);
    return (0);
}

