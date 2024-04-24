/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olena <olena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:25:46 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/24 17:42:50 by olena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Set exit status to 128 + signal number
        else
Set exit status to 127 if command not found*/
void exit_status(t_mnshll *minsh, pid_t pid, int com_run)
{
    int status;

    status = 0;
    if (minsh->command_amount == 1 && isbuilt(minsh->cmdlist->tokens[0]))
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
