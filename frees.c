/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:06:39 by otolmach          #+#    #+#             */
/*   Updated: 2024/06/23 21:18:36 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_two_error(t_mnshll *minsh, int fd, int *pipe_fd)
{
	if (fd != -123456)
		close(fd);
	if (pipe_fd != NULL)
		close_fd(pipe_fd);
	free_exit_procces(minsh, "Error: dup2 fail!");
}

void	free_heredoc(t_mnshll *minsh, int fd)
{
	int	exit_s;

	close(fd);
	free(minsh->heredoc_buf);
	exit_s = minsh->exit;
	if (minsh->input)
		free(minsh->input);
	free_all_arrays(minsh->com_array);
	if (minsh->envl)
		free_env(minsh->envl);
	close(0);
	close(1);
	if (minsh->fdin != -1)
		close(minsh->fdin);
	if (minsh->fdout != -1)
		close(minsh->fdout);
	if (minsh)
		free(minsh);
	rl_clear_history();
	exit(exit_s);
}

void	free_cmd_list(t_lexer *cmdlist)
{
	t_lexer	*tmp;
	t_lexer	*next_node;

	tmp = cmdlist;
	while (tmp != NULL)
	{
		next_node = tmp->next;
		if (tmp->tokens != NULL)
			free(tmp->tokens);
		free(tmp);
		tmp = next_node;
	}
}

void	free_to_main(t_mnshll *minsh)
{
	check_global_end();
	handler_cd(minsh);
}

void	free_exit_procces(t_mnshll *minsh, char *mess)
{
	int	exit_s;

	exit_s = minsh->exit;
	if (mess != NULL)
		ft_putstr_fd(mess, STDERR_FILENO);
	if (minsh->input)
		free(minsh->input);
	if (minsh->list_com)
		free_cmd_list(minsh->list_com);
	if (minsh->com_array)
		free_all_arrays(minsh->com_array);
	if (minsh->envl)
		free_env(minsh->envl);
	close(0);
	close(1);
	close(2);
	if (minsh->fdin != -1)
		close(minsh->fdin);
	if (minsh->fdout != -1)
		close(minsh->fdout);
	if (minsh)
		free(minsh);
	rl_clear_history();
	exit(exit_s);
}
