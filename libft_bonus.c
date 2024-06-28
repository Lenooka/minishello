/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:28:41 by jhuber            #+#    #+#             */
/*   Updated: 2024/06/24 22:40:08 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int	get_flag(t_mnshll *ms, char *ident, char *new_con, char *content)
{
	if (!ft_strchr(content, '='))
	{
		if (find_ident(ms->envl, ident, new_con, 2) == 2)
			return (4);
		else if (find_ident(ms->envl, ident, new_con, 2) == 1)
			return (0);
		else
			return (3);
	}
	else
	{
		if (find_ident(ms->envl, ident, new_con, 1) == 2)
			return (2);
		else
			return (1);
	}
	return (0);
}
*/

void	ft_lstadd_front(t_envl **lst, t_envl *new)
{
	new->next = *lst;
	*lst = new;
}

t_envl	*ft_envnew(void *input)
{
	t_envl	*top;

	top = malloc(sizeof(t_envl));
	if (!top)
		return (NULL);
	if (ft_strchr(input, '=') == 0)
		top->equal_flag = 0;
	else
		top->equal_flag = 1;
	top->identificator = get_ident(input, '=');
	top->content = get_cont(input, '=');
	top->next = NULL;
	return (top);
}
