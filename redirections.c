/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:54:25 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/17 17:33:04 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirout(t_mnshll *minsh, char *check, char *filename, int process)
{
	if (ft_strcmp(check, ">") == 0)
		return (output_redir(minsh, filename, process));
	else if (ft_strcmp(check, "<<") == 0)
		return (append_out_redir(minsh, filename, process));
	return (0);
}

int	redirin(t_mnshll *minsh, char *check, char *filename, int process)
{
	if (ft_strcmp(check, "<") == 0)
		return (input_redir(minsh, filename, process));
	else if (ft_strcmp(check, "<<") == 0)
		return (heredoc_redir(minsh, filename, process));
	return (0);
}

int	redir(t_mnshll *minsh, char **array, int pos, int process)
{
	int	i;
	int	result;

	i = pos;
	result = 0;
	while (array[i] && array[i][0] && ft_strcmp(array[i], "|" != 0))
	{
		result += redirin(minsh, array[i], array[i + 1], process);
		result += redirout(minsh, array[i], array[i + 1], process);
		i++;
		if (result > 0)
			return (1); 
	}
	return (0);
}