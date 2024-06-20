/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 18:27:56 by otolmach          #+#    #+#             */
/*   Updated: 2024/06/20 09:23:51 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_and_close(t_mnshll *m, int fd, int op, int *pipefd)
{
	if (op == 1)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			dup_two_error(m, fd, pipefd);
	}
	else if (op == 2)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			dup_two_error(m, fd, pipefd);
	}
}

/* setup fd for inp and outp 
if one command and its a built in free/execute in a parent
else
function for execution (simmilar to pipex???)*/
void	 child(t_mnshll *ms, int *pipe_fd, int cmds_run, int pos)
{
	t_lexer		*cmd;
	char		**new_cmds;
	int			i;

	new_cmds = NULL;
	cmd = ms->list_com;
	i = cmds_run;
	signal(SIGPIPE, signal_global);
	while (i > 0)
	{
		cmd = cmd->next;
		i--;
	}
	if (cmds_run != 0)
	{
		redirect_and_close(ms, ms->fd_cmd, 1, pipe_fd);
		close(ms->fd_cmd);
	}
	if (cmds_run < ms->command_amount - 1)
		redirect_and_close(ms, pipe_fd[1], 2, pipe_fd);
	close_fd(pipe_fd);
	if ((ms->command_amount == 1) && isbuilt(cmd->tokens[0]))
		free_exit_procces(ms, NULL);
	redir(ms, ms->com_array, pos, 1);
	exe_cutie(ms, cmd->tokens, new_cmds);
}
/*if one command and is a built,check redir succs if yes close the pipe fd!!
and call builtin
if there more than one close the fd for prev command
 if not last command close change fd
 close pipe fd and set signal to SIGINT
*/

void	parent(t_mnshll *m, int *pipe_fd, int cmrun, int pos)
{
	t_lexer	*cmnds;
	int		fd_flag;

	fd_flag = 0;
	pos = 0;
	cmnds = m->list_com + cmrun;
	if (m->command_amount == 1)
	{
		if(isbuilt(cmnds->tokens[0]) && redir(m, m->com_array, pos, 0) == 0)
		{
			fd_flag = 1;
			built_ex(m, cmnds->tokens);
		}
	}
	if (cmrun > 0)
		close(m->fd_cmd);
	if (cmrun < m->command_amount - 1)
		m->fd_cmd = pipe_fd[0];
	else
		close(pipe_fd[0]);
	if (fd_flag == 1)
		close_fd(pipe_fd);
	close(pipe_fd[1]);
	signal(SIGINT, signal_global);
}


void    start_procces(t_mnshll *minsh)
{
    int     com_run;
    pid_t   pid;
    int     position;

    com_run = 0;
	position = 0;
	if (!minsh->list_com)
		return ;
    while (com_run < minsh->command_amount)
    {
		if (pipe(minsh->pipefd) == -1)
			pepe_error(minsh, minsh->pipefd);
		pid = fork();
		if (pid == 0)
			child(minsh, minsh->pipefd, com_run, position);
		else if (pid < 0)
			fork_error(minsh, minsh->pipefd);
		else
			parent(minsh, minsh->pipefd, com_run, position);
		position = find_com_pos(minsh->com_array, position);
		com_run++;
    }
	exit_status(minsh, pid, com_run);
}

void	minishell(t_mnshll *mnshll)
{
	mnshll->extra = 0;
	start_procces(mnshll);
	free_cmd_list(mnshll->list_com);
	mnshll->list_com = NULL;
	free_all_arrays(mnshll->com_array);
	mnshll->com_array = NULL;
}
