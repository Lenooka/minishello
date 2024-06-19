/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 03:35:28 by jhuber            #+#    #+#             */
/*   Updated: 2024/06/19 19:29:55 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_mnshll *mini)
{
	t_envl	*tmp;

	if (!mini->envl)
	{
		error_msg(mini, "environment variable list not set", 1, "env");
		return ;
	}
	tmp = *mini->envl;
	if (!tmp)
		return ;
	while (tmp)
	{
		if ((tmp)->node_flag == 1)
			ft_printf("%s=%s\n", (tmp)->identificator, (tmp)->content);
		tmp = (tmp)->next;
	}
	return ;
}
