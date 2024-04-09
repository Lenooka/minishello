/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:33:06 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/09 13:21:43 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	init_fds(t_mnshll *minsh)
{
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
		printf("Tokenizing fail!") //should exit free here?
		return (1);
	}
	if (init_heredoc(minsh, minsh->com_array) == 1)
		return (1);
	repl_var_array = replace_var(minsh);
	
	
}
