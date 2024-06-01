/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exstart_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:18:04 by olena             #+#    #+#             */
/*   Updated: 2024/06/01 15:43:12 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
