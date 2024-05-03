/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_extras.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:06:37 by jhuber            #+#    #+#             */
/*   Updated: 2024/04/28 20:10:38 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_oldpath(t_envl **envl, char *oldpath)
{
	t_envl	tmp;
	char	*new_content;

	tmp = *envl;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (strcmp((char *)(tmp)->identificator, "OLDPWD") == 0)
		{
			new_content = ft_strdup(oldpath);
			free((tmp)->content);
			(tmp)->content = new_content;
			break ;
		}
		tmp = (tmp)->next;
	}
}

void	list_swap(t_mnshll *mini, t_envl *list)
{
	char	*ident;
	void	*content;
	t_envl	*top;
	t_envl	*tmp;

	ident = NULL;
	content = NULL;
	top = list;
	if (!top && !top->next)
	{
		write(2, "List Swap Error\n", 16);		//error changes
		mini->exit = 1;
		return ;
	}
	tmp = top;
	ident = tmp->ident;
	content = tmp->content;
	top->ident = top->next->ident;
	top->content = top->next->content;
	top->next->ident = ident;
	top->next->content = content;
}
