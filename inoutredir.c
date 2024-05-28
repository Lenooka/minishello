/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inoutredir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:34:42 by otolmach          #+#    #+#             */
/*   Updated: 2024/05/28 13:34:52 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_redir(t_mnshll *minsh, char *filename, int procces)
{
	int		fd;
	char	*file;

	file = remove_quotes(filename);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		open_error(minsh, filename, procces);
		return (1);
	}
	else
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			dup_two_error(minsh, -123456, NULL);
		close(fd);
	}
	free(file);
	return (0);
}

int	heredoc_redir(t_mnshll *minsh, char *filename, int procces)
{
	int		fd;
	char	*file;

	file = remove_quotes(filename);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		open_error(minsh, filename, procces);
		return (1);
	}
	else
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			dup_two_error(minsh, -123456, NULL);
		close(fd);
		if (unlink(file) == -1)
			free_exit_procces(minsh, "Error: unlink fail!");
	}
	free(filename);
	free(file);
	return (0);
}

int	output_redir(t_mnshll *minsh, char *filename, int process)
{
	int		fd;
	char	*file;

	file = remove_quotes(filename);
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (fd < 0)
	{
		open_error(minsh, filename, process);
		return (1);
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			dup_two_error(minsh, -123456, NULL);
		close(fd);
	}
	free(file);
	return (0);
}

int	append_out_redir(t_mnshll *minsh, char *filename, int process)
{
	int		fd;
	char	*file;

	file = remove_quotes(filename);
	fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0664);
	if (fd < 0)
	{
		open_error(minsh, filename, process);
		return (1);
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			dup_two_error(minsh, -123456, NULL);
		close(fd);
	}
	free(file);
	return (0);
}
