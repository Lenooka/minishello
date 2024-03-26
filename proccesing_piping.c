/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccesing_piping.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:27:56 by otolmach          #+#    #+#             */
/*   Updated: 2024/03/26 18:28:22 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (pid != 0)
			position = 0;
			//parrent
		else
			position = 0;
            //child
		position = find_com_pos(mnshll->com_array, position);
    }
	exit_status(mnshll, pid, com_run);
}