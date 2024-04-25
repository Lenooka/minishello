/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:25:46 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/25 17:13:18 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_fd(t_mnshll *minsh)
{
	if (dup2(minsh->fdin, STDIN_FILENO) == -1)
		dup_two_error(minsh, -123456, NULL);
	if (dup2(minsh->fdout, STDOUT_FILENO) == -1)
		dup_two_error(minsh, -123456, NULL);
	if (minsh->fdin != 0)
		close(minsh->fdin);
	if (minsh->fdout != 1)
		close(minsh->fdout);
}

/*
WIFEXITED and WEXITSTATUS used to know the exit status of the child. 
WIFEXITED(status) : returns true if the child terminated normally.
WEXITSTATUS(status) : returns the exit status of the child. 
This macro should be employed only if WIFEXITED returned true.
If WIFSIGNALED is true of status , this macro returns the signal 
number of the signal that terminated the child process.  
Set exit status to 128 + signal number
        else
Set exit status to 127 if command not found

if i exit my life what would be my exit status
	-1
*/
void exit_status(t_mnshll *minsh, pid_t pid, int com_run)
{
    int status;

    status = 0;
    if (minsh->command_amount == 1 && isbuilt(minsh->list_com->tokens[0]))
    {
        wait(&status);
        reset_fd(minsh);
        return ;
    }
    while (com_run > 0) 
	{
        wait(&status);
        if (pid != -1 && WIFEXITED(status))
            minsh->exit = WEXITSTATUS(status);
        else if (pid != -1 && WIFSIGNALED(status))
            minsh->exit = 128 + WTERMSIG(status);
        else
            minsh->exit = 127;
        com_run--;
    }
    reset_fd(minsh); 
}
