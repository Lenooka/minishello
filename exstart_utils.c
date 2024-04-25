/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exstart_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olena <olena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:18:04 by olena             #+#    #+#             */
/*   Updated: 2024/04/25 20:17:25 by olena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_com_pos(char **arr, intn pos)
{
	int	i;

	i = pos;
	while (arr[i] && arr[i][0] && ft_strcmp(arr[i], "|" )!= 0)
		i++;
	if (arr[i] && arr[i][0] && ft_strcmp(arr[i], "|" )== 0)
		i++;
	return (i);
}