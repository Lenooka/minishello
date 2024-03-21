/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:03:20 by otolmach          #+#    #+#             */
/*   Updated: 2024/03/21 21:58:24 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_com_pos(char **com_array, int	pos)
{
	//find position untill "|"
}

void exit_status(t_mnshll *mnshll, pid_t pid, int com_run) 
{
    int status;
    int last_status = 0;
    int any_command_failed = 0;

    if (mnshll->command_amount == 1) // and is builtin 
	{
        wait(&status);
		//reset file descriptors
        return;
    }
    while (com_run > 0) 
	{
        wait(&status);
        if (pid != -1 && WIFEXITED(status))  //if child evaluate properly
		{
            last_status = WEXITSTATUS(status); // gets exit status and updates last_status
            if (last_status == 127) 
                any_command_failed = 1;
        } 
		else if (pid != -1 && WIFSIGNALED(status)) //checking if process term with signal 
		{
            g_global = WTERMSIG(status); // gets exit status of the signal
            any_command_failed = 1; //command failed due to a signal not sure about this one
        }
        com_run--;
    }
    if (any_command_failed == 1)
        mnshll->exit = 127;
    else
        mnshll->exit = last_status;
	//reset file descriptors
}

void	exit_status(t_mnshll *ms, pid_t pid, int com_run) 
{
    int status;
    int last_status = 0; 
    
    if (mnshll->command_amount == 1 )//and its a builtin
	{
        wait(&status);
    //reset file desrp;
        return ;
    }
    while (com_run > 0) 
	{
        wait(&status);
        if (pid != -1 && WIFEXITED(status)) //if child evaluate properly
            last_status = WEXITSTATUS(status); // gets exit status and updates last_status
        if (pid != -1 && WIFSIGNALED(status))  //checking if process term with signal 
            g_global = WTERMSIG(status); // gets exit status of the signal
        else
            g_global = 0;
        com_run--;
    }    
    mnshll->exit = last_status; 
    //reset file desrp;
}


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
	exit_status(mnshll, pid, com_run);
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

