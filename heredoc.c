/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olena <olena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:10:00 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/23 22:26:14 by olena            ###   ########.fr       */
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
	if (spec_strcmp(out, line, '\n') == 0) //write a special strcmp
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
	ft_exit(minsh);//free_hdoc(minsh);
}

void	init_heredoc(t_mnshll *minsh, char *del, int num_indx)
{
	int		fd;
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	fd = file_des_create(minsh, num_indx);
	pid = fork();
	if (pid == 0 && fd != 0)
	{
		signal(SIGINT, heredoc_signal_handle); //signal fucntion for U JOEL <;
		heredoc_child(minsh, fd, del);
	}
	else if (pid < 0 || fd < 0)
		exit(1);//forkerror not check fd for null closing fd
	else
	{
		waitpid(pid, &status, 0);
		if (pid != -1 && WIFEXITED(status) && WEXITSTATUS(status) == (128 + \
			SIGINT))
		{
			g_global = SIGINT;
			unlink(minsh->heredoc_buf);
		}
	}
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
			init_heredoc(minsh, str[i + 1], i);
			free(str[i + 1]);
			str[i + 1] = ft_strdup(minsh->heredoc_buf);
			free(minsh->heredoc_buf);
			if (g_global == SIGINT)
			{
				g_global = 0;
				return (1);
			}
			i += 2;
		}
		else
			i++;
	}
	return (0);
}
