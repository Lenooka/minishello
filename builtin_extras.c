/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_extras.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:06:37 by jhuber            #+#    #+#             */
/*   Updated: 2024/04/24 18:39:29 by jhuber           ###   ########.fr       */
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