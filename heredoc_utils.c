/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:20:11 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/13 16:25:54 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_file(t_mnshll *minsh, char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		ft_exit(minsh);//error handle open errors
	return (fd);
}

int	file_des_create(t_mnshll *minsh, int here_num)
{
	int		i;
	char	*tmp;
	int		fd;

	i = 0;
	tmp = NULL;
	minsh->heredoc_buf = ft_strdup("/tmp/minshl");
	while (i < here_num)
	{
		tmp = ft_strdup(minsh->heredoc_buf);
		free(minsh->heredoc_buf);
		if (tmp == NULL)
			return (-1);
		minsh->heredoc_buf = ft_strjoin(tmp, "l");
		free(tmp);
		if (minsh->heredoc_buf == NULL)
			return (-1);
		i++;
	}
	fd = create_file(minsh, minsh->heredoc_buf);
	return (fd);
}

void	heredoc_warn(char *del)
{
	//t_mnshll *m = NULL;
	ft_putstr_fd("Minishell: warning: here-document delimited ", STDERR_FILENO);
	ft_putstr_fd("by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(del, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
	//ft_exit(m);
}

void	disable_quit_signals(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	heredoc_signal_handle(int signal)
{
	if (signal == SIGINT)
	{
		g_global = SIGINT;
		printf("\n");
		close(STDIN_FILENO);
	}
}
