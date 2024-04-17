/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:54:25 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/17 15:59:09 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir(t_mnshll *minsh, char **array, int pos, int process)
{
	int	i;
	int	res;

	i = pos;
	res = 0;
	while (array[i] && array[i][0] && ft_strcmp(array[i], "|" != 0))
	{
		
	}
}