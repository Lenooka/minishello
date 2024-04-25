/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:57:05 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/25 15:58:51 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}