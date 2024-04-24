/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:06:39 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/24 12:53:45 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_list(t_lexer *cmdlist)
{
	t_lexer	*tmp;
	t_lexer	*head;

	head = cmdlist;
	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->tokens)
			free(tmp->tokens);
		free(tmp);
	}
}

void	ft_exit(t_mnshll *m)
{
	m->exit = 1;
	exit(1);
}
