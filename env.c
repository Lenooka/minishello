/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 03:35:28 by jhuber            #+#    #+#             */
/*   Updated: 2024/04/26 04:37:45 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_mnshll *mini)
{
	if (mini->env == NULL)
	{
		error;		//Error handling, message, frees needed.
		return ;
	}
	print_lst(ms->env, 1);
}
