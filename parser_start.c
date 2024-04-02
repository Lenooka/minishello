/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:33:06 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/02 16:04:39 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	init_fds(t_mnshll *minsh)
{
	minsh->fdin = dup(STDIN_FILENO);
	if (minsh->fdin == -1)
		return (1);
	minsh->fdout = dup(STDOUT_FILENO);
	if (minsh->fdout == -1)
		return (1);
	return (0);
}

char	**split_tokenize(t_mnshll *minsh)
{
	char	**result;

	
}

int	parser_start(t_mnshll *minsh)
{
	if (init_struct_stuff(minsh) == 1)
		return (1);
	minsh->com_array = split_tokenize(minsh);
	
}