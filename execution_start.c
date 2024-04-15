/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:27:56 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/15 18:49:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(t_mnshll *ms, int *pipe_fd, int cmds_run, int pos)
{
	t_lexer		*cmd;
	char		**new_cmds;
	int			i;

	new_cmds = NULL;
	cmd = ms->cmdlist;
	i = cmds_run;
	signal(SIGPIPE, signal_global);
	while (i > 0)
	{
		cmd = cmd->next;
		i--;
	}
	if (cmds_run != 0)
	{
		dup2(ms->cmd_fd, STDIN_FILENO);
		close(ms->cmd_fd);
	}
	if (cmds_run < ms->cmd_count - 1)
		dup2(pipe_fd[1], STDOUT_FILENO);
	close_fd(pipe_fd);
	if (ms->cmd_count == 1 && isbuiltin(cmd->cmds[0]))
		free_ms(ms);
	redirect(ms, ms->main_arr, pos, 1);
	exec(ms, cmd->cmds, new_cmds);
}

 /*if one command and is a built,check redir succs if yes close the pipe fd!!
 and call builtin
 if there more than one close the fd for prev command
 if not last command close change fd
 close pipe fd and set signal to SIGINT
 */
void	parent(t_mnshll *m, int *pipe_fd, int cmrun, int pos)
{
	t_lexer *cmnds;
	int		shred;
	int		fd_flag;

	cmnds = m->list_com + cmrun;
	shred = isbuilt(cmnds->tokens[0]) && redir(m, m->com_array, pos, 0) == 0;
	if (m->command_amount == 1)
	{
		if(shred == 1)
		{
			fd_flag = 1;
			built_ex(m, cmnds->tokens);  //non function yet
		}
	}
	if (cmrun > 0)
		close(m->fd_cmd);
	if (cmrun < m->command_amount - 1)
		m->fd_cmd = pipe_fd[0];
	else
		close(pipe_fd[0]);
	if (fd_flag == 1)
		close_fd(pipe_fd);  //non function yet
	close(pipe_fd[1]);
	signal(SIGINT, signal_global);
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
