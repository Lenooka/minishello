/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:10:00 by otolmach          #+#    #+#             */
/*   Updated: 2024/06/14 14:32:04 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*hrdc_out(t_mnshll *minsh, char	*del, char *line)
{
	char	*out;

	if (g_global == SIGINT || !line)
		return (NULL);
	out = remove_quotes(del);
	if (!out)
		return (NULL);
	if (spec_strcmp(out, line, '\n') == 0)
	{
		free(out);
		return (NULL);
	}
	free(out);
	if (!ft_strchr(del, '\'') && !ft_strchr(del, '\"'))
		out = replace_var_in_str(minsh, line);
	else
	out = ft_strdup(line);
	return (out);
}

void	free_and_null(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	heredoc_child(t_mnshll *minsh, int fd, char *del)
{
	char	*output;
	char	*line;

	line = NULL;
	while (1)
	{
		disable_quit_signals();
		line = readline("> ");
		if (g_global == SIGINT)
			minsh->exit = 128 + SIGINT;
		else if (line == NULL)
			heredoc_warn(del);
		output = hrdc_out(minsh, del, line);
		if (!output)
			break ;
		free_and_null((void **)&line);
		ft_putendl_fd(output, fd);
		free_and_null((void **)&output);
	}
	if (line)
		free_and_null((void **)&line);
	close(fd);
	free_heredoc(minsh, fd);
}

void	start_heredoc(t_mnshll *minsh, char *del, int num_indx)
{
	int		fd;
	pid_t	pid;
	int		status;

	fd = file_des_create(minsh, num_indx);
	pid = fork();
	if (pid == 0 && fd != 0)
	{
		signal(SIGINT, heredoc_signal_handle);
		heredoc_child(minsh, fd, del);
		close(fd);
	}
	else if (pid < 0 || fd < 0)
		fork_error(minsh, NULL);
	else
	{
		waitpid(pid, &status, 0);
		if (pid != -1 && WIFEXITED(status) && WEXITSTATUS(status)
			== (128 + SIGINT))
		{
			g_global = SIGINT;
			unlink(minsh->heredoc_buf);
		}
	}
}
int	init_heredoc(t_mnshll *minsh, char **str, int i)
{
	start_heredoc(minsh, str[i + 1], i);
	free(str[i + 1]);
	str[i + 1] = ft_strdup(minsh->heredoc_buf);
	free(minsh->heredoc_buf);
	if (g_global == SIGINT)
	{
		g_global = 0;
		return (1);
	}
	return (0);
}

int	if_there_heredoc(t_mnshll *minsh, char **str)
{
	int		i;

	i = 0;
	if (!str || !str[0] || !str[0][0])
		return (0);
	while (str[i])
	{
		if (ft_strcmp(str[i], "<<") == 0)
		{
			if (init_heredoc(minsh, str, i) == 1)
				return (1);
			i++;
			i++;
		}
		else
			i++;
	}
	return (0);
}
