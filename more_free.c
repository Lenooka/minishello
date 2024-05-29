/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:57:05 by otolmach          #+#    #+#             */
/*   Updated: 2024/05/29 13:25:49 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_error(t_mnshll *minsh, char *filename, int process)
{
	if (process)
	{
		ft_putstr_fd("Error : ", STDERR_FILENO);
		perror(filename);
		if (filename)
			free(filename);
		minsh->exit = 1;
		minsh->extra = 1;
		free_exit_procces(minsh, NULL);
	}
	else
	{
		ft_putstr_fd("Error : ", STDERR_FILENO);
		perror(filename);
		minsh->exit = 1;
		minsh->extra = 1;
		return (1);
	}
	return (0);
}

void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	pepe_error(t_mnshll *minsh, int *fd)
{
	close_fd(fd);
	minsh->exit = 1;
	free_exit_procces(minsh, "Error: Pipe fail 🐸");
}

void	fork_error(t_mnshll *minsh, int *fd)
{
	if (fd != NULL)
		close_fd(fd);
	minsh->exit = 1;
	free_exit_procces(minsh, "Error: Fork fail");
}

void	free_exit_out_all(t_mnshll *minsh, char *mess)
{
	int	exit_s;

	exit_s = minsh->exit;
	if (mess != NULL)
		write(STDERR_FILENO, mess, ft_strlen(mess));
	if (minsh->input)
		free(minsh->input);
	if (minsh->list_com)
		free_cmd_list(minsh->list_com);
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