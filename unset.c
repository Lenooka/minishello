/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:14:17 by jhuber            #+#    #+#             */
/*   Updated: 2024/05/29 17:24:38 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	valid_ident(char *str)
{
	int	x;
	int	flag;

	if (ft_strcmp(str, "_") == 0)
		return (2);
	if ((str[0] >= '0' && str[0] <= '9') || str[0] == '=')
		return (0);
	x = 0;
	flag = 0;
	while (str[x])
	{
		if ((str[x] >= 'a' && str[x] <= 'z') || (str[x] >= '0' && str[x] <= '9')
			|| (str[x] >= 'A' && str[x] <= 'Z') || str[x] == '_')
			flag = 1;
		else
			return (0);
		x++;
	}
	if (flag == 1)
		return (1);
	return (0);
}

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
	while (lst->next)		//Small change here from != NULL
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
