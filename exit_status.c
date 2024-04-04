/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:25:46 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/04 13:32:56 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exit_status(t_mnshll *mnshll, pid_t pid, int com_run)
{
    int status;
    int last_status = 0;

	last_status = 0;
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
            //if (last_status == 127) 
               // any_command_failed = 1;
        } 
		else if (pid != -1 && WIFSIGNALED(status)) //checking if process term with signal 
		{
            g_global = WTERMSIG(status); // gets exit status of the signal
            //any_command_failed = 1; //command failed due to a signal not sure about this one
        }
        com_run--;
    }
   // if (any_command_failed == 1)
       /// mnshll->exit = 127; this is is not correct most probably
        mnshll->exit = last_status;
	//reset file descriptors
}
