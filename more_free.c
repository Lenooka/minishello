/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:57:05 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/25 17:07:20 by otolmach         ###   ########.fr       */
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
		free_exit_procces(minsh, NULL);
	}
	else
	{
		ft_putstr_fd("Error : ", STDERR_FILENO);
		perror(filename);
		if (filename)
			free(filename);
		minsh->exit = 1;
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
	free_exit_proccess(minsh, "Error: Pipe fail 🐸");
}

void	fork_error(t_mnshll *minsh, int *fd)
{
	if (fd != NULL)
		close_fd(fd);
	minsh->exit = 1;
	free_exit_proccess(minsh, "Error: Fork fail");
}