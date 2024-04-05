/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olena <olena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:10:00 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/05 22:02:35 by olena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	disable_quit_signals(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	free_and_null(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	heredoc_child(t_minishell *ms, int fd, char *del)
{
	char	*output;
	char	*line;

	line = NULL;
	while (1)
	{
		disable_quit_signals();
		line = readline("> ");
		if (g_global == SIGINT)
			ms->exit = 128 + SIGINT;
		else if (!line)
			heredoc_eof(limiter);
		output = heredoc_output(ms, limiter, line);
		if (!output)
			break ;
		free_and_null((void **)&line);
		ft_putendl_fd(output, fd);
		free_and_null((void **)&output);
	}
	free_and_null((void **)&line);
	close(fd);
	free_hdoc(ms);
}

int	create_file(t_minishell *ms, char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		 //error handle open errors
	free(filename);
	return (fd);
}

int	file_des_create(t_mnshll *minsh, int here_num)
{
	int		i;
	char	*tmp;
	int		fd:

	i = 0;
	tmp = NULL;
	minsh->heredoc_buf = ft_strdup("/tmp/minshl");
	while (i < here_num)
	{
		tmp = ft_strdup(minsh->heredoc_buf);
		free(minsh->heredoc_buf);
		if (buf == NULL)
			return (-1);
		minsh->heredoc_buf = ft_strjoin(buf, "l");
		free(tmp);
		if (minsh->heredoc_buf == NULL)
			return (-1);
		i++;
	}
	fd = create_file(minsh, minsh->heredoc_buf);
	return (fd);
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
		siganl(SIGINT, heredoc_signal_handle); //signal fucntion for U JOEL <;
		heredoc_child(minsh, fd, del);
	}
	else if (pid < 0 || fd < 0)
		//forkerror not check fd for null closing fd
	else
	{
		waitpid(pid, &status, 0);
		if (pid != -1 && WIFEXITED(status) && WEXITSTATUS(status) == (128 + \
			SIGINT))
		{
			g_global = SIGINT;
			unlink(file);
		}
	}
}

int	if_there_heredoc(t_mnshll *minsh, char **str)
{
	int		i;

	i = 0;
	if (!str || !str[0] || !str[0][0])
		return (1);
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
