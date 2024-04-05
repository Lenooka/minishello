/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:10:00 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/05 13:05:51 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_heredoc(t_mnshll *minsh, char *str, int indx)
{
	
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
