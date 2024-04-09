/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:33:06 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/09 17:06:54 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	init_fds(t_mnshll *minsh)
{
	minsh->rep_var_i = 0;
	minsh->fd_cmd = 0;
	minsh->fdin = dup(STDIN_FILENO);
	if (minsh->fdin == -1)
		return (1);
	minsh->fdout = dup(STDOUT_FILENO);
	if (minsh->fdout == -1)
		return (1);
	return (0);
}


int	parser_start(t_mnshll *minsh)
{
	char	**repl_var_array;
	if (init_fds(minsh) == 1)
		return (1);
	minsh->com_array = split_tokenize(minsh, minsh->input);
	if (minsh->com_array == NULL)
	{
		printf("Tokenizing fail!\n"); //should exit free here?
		return (1);
	}
	if (if_there_heredoc(minsh, minsh->com_array) == 1)
		return (1);
	repl_var_array = replace_var(minsh);
	if (repl_var_array == NULL)
	{
		printf("Replacing of variabls failed!\n"); //should exit free here??
		return (1);
	}
	
}
