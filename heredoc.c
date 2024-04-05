/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olena <olena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:10:00 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/05 14:50:06 by olena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_heredoc(t_mnshll *minsh, char *del, int num_indx)
{
	char	*file;
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	file = create_file(num_indx);
	pid = fork();
	if (pid == 0)
	{
		siganl(SIGINT, heredoc_signal_handle);
		heredoc_child(minsh, file, del);
	}
	else if (pid < 0)
	{
		//forkerror
	}
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
	return (file);
}

int	if_there_heredoc(t_mnshll *minsh, char **str)
{
	int		i;
	char	*towr;

	i = 0;
	if (!str || !str[0] || !str[0][0])
		return (1);
	while (str[i])
	{
		if (ft_strcmp(str[i], "<<") == 0)
		{
			towr = init_heredoc(minsh, str[i + 1], i);
			free(str[i + 1]);
			str[i + 1] = ft_strdup(towr);
			free(towr);
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
