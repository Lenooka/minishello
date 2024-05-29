/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 03:35:28 by jhuber            #+#    #+#             */
/*   Updated: 2024/05/29 17:15:23 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lst(t_envl **lst, int flag)
{
	t_envl	*tmp;
	char	*exp;

	exp = "declare -x";
	tmp = *lst;
	if (!tmp)
		return ;
	if (flag == 2)
		exp = "declare -x";
	while (tmp)
	{
		if ((tmp)->node_flag == 1 && flag == 1)
			ft_printf("%s=%s\n", (tmp)->identificator, (tmp)->content);
		else if (flag == 2)
		{
			if ((tmp)->equal_flag == 0 && ft_strcmp((tmp)->content, "  ") == 0)
				ft_printf("%s%s%s %s\n", exp, (tmp)->identificator);
			else if (ft_strcmp((tmp)->content, "  ") == 0)
				ft_printf("%s%s%s %s=\"\"\n", exp, (tmp)->identificator);
			else
				ft_printf("%s%s%s %s=\"%s\"\n", exp, \
					(tmp)->identificator, (tmp)->content);
		}
		tmp = (tmp)->next;
	}
}

void	env(t_mnshll *mini)
{
	if (mini->envl == NULL)
	{
		error_msg(mini, "environment variable list not set", 1, "env");
		return ;
	}
	print_lst(mini->envl, 1);
}
