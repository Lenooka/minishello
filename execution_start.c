/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:27:56 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/13 17:05:02 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent(t_mnshll *minsh, int *pipe_fd, int cmrun, int pos)
{
	t_lexer *cmnds;
	int		i;

	i = 0;
	cmnds = minsh->list_com;
}

void    start_procces(t_mnshll *minsh)
{
    int     com_run;
    int     pipefd[2];
    pid_t   pid;
    int     position;

    com_run = 0;
	position = 0;
	if (!minsh->list_com)
		return ;
    while (com_run < minsh->command_amount) //the amount of the commands from parser
    {
		if (pipe(pipefd) == -1)
		{
			//free_error
		}
		pid = fork();
		if (pid < 0)
		{
			//free_error
		}
		if (pid != 0)
		{
			position = 0; //parent
		}
		else if (position == 0)
		{
			position = 0; //child
		}
		position = find_com_pos(mnshll->com_array, position);
		com_run++;
    }
	exit_status(mnshll, pid, com_run);
}

void	minishell(t_mnshll *mnshll)
{
	printf("WELLDONE\n");
	printf("%s\n", mnshll->input);
	//start_procces(mnshll);
	free_cmd_list(mnshll->list_com);
}
