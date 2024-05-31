/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_empty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:51:25 by jhuber            #+#    #+#             */
/*   Updated: 2024/05/31 14:20:54 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envl	*node(t_envl *new, t_envl *env)
{
	new = malloc(sizeof(t_envl));
	new->identificator = ft_strdup(env->identificator);
	new->content = ft_strdup((char *)env->content);
	new->next = NULL;
	return (new);
}

void	print_table(t_envl **env)
{
	t_envl	*curr;

	curr = *env;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->identificator, "_") == 0)
		{
			if (curr->next)
				curr = curr->next;
			else
				break ;
		}
		ft_printf("%s %s=\"%s\"\n", "declare -x", curr->identificator, curr->content); //Not sure if I changed this printf correctly, gotta check later
		curr = curr->next;
	}
}

void	sort_env(t_mnshll *mini, t_envl **env)
{
	int		swap;
	t_envl	*ptr1;
	t_envl	*lptr;

	swap = 1;
	lptr = NULL;
	while (swap)
	{
		swap = 0;
		ptr1 = *env;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->identificator, ptr1->next->identificator))
			{
				list_swap(mini, ptr1);
				swap = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

t_envl	*copy_envl(t_envl *env)
{
	t_envl	*top;
	t_envl	*bottom;
	t_envl	*new;

	top = NULL;
	bottom = NULL;
	new = NULL;
	while (env)
	{
		new = node(new, env);
		if (bottom == NULL)
		{
			top = new;
			bottom = new;
		}
		else
		{
			bottom->next = new;
			bottom = new;
		}
		env = env->next;
	}
	return (top);
}

void	export_empty(t_mnshll *mini)
{
	t_envl	*tmp;
	t_envl	*next;
	t_envl	*curr;

	if ((*mini->envl) == NULL || (*mini->envl)->identificator == NULL)
		return ;
	tmp = copy_envl(*mini->envl);
	sort_env(mini, &tmp);
	print_table(&tmp);
	curr = tmp;
	while (curr)
	{
		next = curr->next;
		free(curr->identificator);
		free(curr->content);
		free(curr);
		curr = next;
	}
}
