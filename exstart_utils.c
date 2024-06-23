/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exstart_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:18:04 by olena             #+#    #+#             */
/*   Updated: 2024/06/23 20:25:24 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_signal(void)
{
	signal(SIGPIPE, signal_global);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

int	find_com_pos(char **arr, int pos)
{
	int	i;

	i = pos;
	while (arr[i] && arr[i][0] && ft_strcmp(arr[i], "|" ) != 0)
		i++;
	if (arr[i] && arr[i][0] && ft_strcmp(arr[i], "|" ) == 0)
		i++;
	return (i);
}
