/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:14:21 by otolmach          #+#    #+#             */
/*   Updated: 2024/05/06 13:08:04 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_ex(t_mnshll *minsh, char **tokens)
{
	minsh->exit = 0;
	tokens = rem_q_from_2d(tokens);
	ft_echo(tokens);
	free_all_arrays(tokens);
}