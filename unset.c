/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:14:17 by jhuber            #+#    #+#             */
/*   Updated: 2024/06/12 13:25:01 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_first(t_envl **env)
{
	t_envl	*tmp;

	tmp = *env;
	(*env) = (*env)->next;
	free(tmp->identificator);
	free(tmp->content);
	free(tmp);
}

void	rm_nodes(t_envl **env, char *str)
{
	t_envl	*tmp;
	t_envl	*lst;

	lst = *env;
	tmp = lst;
	if (!lst)
		return ;
	while (lst->next)
	{
		if (ft_strcmp((char *)(tmp)->identificator, str) == 0)
		{
			rm_first(env);
			break ;
		}
		else if (ft_strcmp((char *)(lst)->next->identificator, str) == 0)
		{
			tmp = lst->next;
			lst->next = lst->next->next;
			free(tmp->identificator);
			free(tmp->content);
			free(tmp);
			break ;
		}
		lst = lst->next;
	}
}

void	unset(t_mnshll *mini, char **input)
{
	int	x;
	int	option;

	x = 1;
	if (!input[x])
		return ;
	while (input[x])
	{
		option = valid_ident(input[x]);
		if (option == 2)
			x++;
		if (option == 0)
			break ;
		rm_nodes(mini->envl, input[x]);
		x++;
	}
}
