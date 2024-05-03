/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isbuilt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:37:13 by otolmach          #+#    #+#             */
/*   Updated: 2024/05/03 13:53:18 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isbuilt(char *com)
{
	if (!com)
		return (0);
	if (ft_strcmp(com, "echo") == 0)
		return (1);
	// //else if (ft_strcmp(com, "cd") == 0)
	// 	return (1);
	// else if (ft_strcmp(com, "pwd") == 0)
	// 	return (1);
	// else if (ft_strcmp(com, "export") == 0)
	// 	return (1);
	// else if (ft_strcmp(com, "unset") == 0)
	// 	return (1);
	// else if (ft_strcmp(com, "env") == 0)
	// 	return (1);
	// else if (ft_strcmp(com, "exit") == 0)
	// 	return (1);
	return (0);
}
