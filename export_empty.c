/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_empty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:51:25 by jhuber            #+#    #+#             */
/*   Updated: 2024/06/23 21:28:28 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_envl	*node(t_envl *new, t_envl *env)
// {
// 	new = malloc(sizeof(t_envl));
// 	new->identificator = ft_strdup(env->identificator);
// 	new->content = ft_strdup((char *)env->content);
// 	new->next = NULL;
// 	return (new);
// }

// void	print_table(t_envl **env)
// {
// 	t_envl	*curr;

// 	curr = *env;
// 	while (curr != NULL)
// 	{
// 		if (ft_strcmp(curr->identificator, "_") == 0)
// 		{
// 			if (curr->next)
// 				curr = curr->next;
// 			else
// 				break ;
// 		}
// 		ft_printf("%s %s=\"%s\"\n", "declare -x",
// 			curr->identificator, curr->content); //Cut this into two lines, does it work? Work on export dumbass
// 		curr = curr->next;
// 	}
// }

// void	sort_env(t_mnshll *mini, t_envl **env)
// {
// 	int		swap;
// 	t_envl	*ptr1;
// 	t_envl	*lptr;

// 	swap = 1;
// 	lptr = NULL;
// 	while (swap)
// 	{
// 		swap = 0;
// 		ptr1 = *env;
// 		while (ptr1->next != lptr)
// 		{
// 			if (ft_strcmp(ptr1->identificator, ptr1->next->identificator))
// 			{
// 				list_swap(mini, ptr1);
// 				swap = 1;
// 			}
// 			ptr1 = ptr1->next;
// 		}
// 		lptr = ptr1;
// 	}
// }

// t_envl	*copy_envl(t_envl *env)
// {
// 	t_envl	*top;
// 	t_envl	*bottom;
// 	t_envl	*new;

// 	top = NULL;
// 	bottom = NULL;
// 	new = NULL;
// 	while (env)
// 	{
// 		new = node(new, env);
// 		if (bottom == NULL)
// 		{
// 			top = new;
// 			bottom = new;
// 		}
// 		else
// 		{
// 			bottom->next = new;
// 			bottom = new;
// 		}
// 		env = env->next;
// 	}
// 	return (top);
// }


// void	export_empty(t_mnshll *mini)
// {
// 	t_envl	*tmp;
// 	t_envl	*next;
// 	t_envl	*curr;

// 	if ((*mini->envl) == NULL || (*mini->envl)->identificator == NULL)
// 		return ;
// 	tmp = copy_envl(*mini->envl);
// 	sort_env(mini, &tmp);
// 	print_table(&tmp);
// 	curr = tmp;
// 	while (curr)
// 	{
// 		next = curr->next;
// 		free(curr->content);
// 		free(curr->identificator);
// 		free(curr);
// 		curr = next;
// 	}
// }

void	get_smallest_biggest(t_envl *envl, t_envl **smallest, t_envl **biggest)
{
	int	x;

	x = 0;
	*smallest = envl;
	*biggest = envl;
	envl = envl->next;
	while (envl)
	{
		x = ft_strncmp(envl->identificator, (*smallest)->identificator, ft_strlen((*smallest)->identificator) + 1);
		if (x < 0)
			*smallest = envl;
		x = ft_strncmp(envl->identificator, (*biggest)->identificator, ft_strlen((*biggest)->identificator) + 1);
		if (x > 0)
			*biggest = envl;
		envl = envl->next;
	}
	printf("%s %s=%s\n", "declare -x", (char *)(*smallest)->identificator, (char *)(*smallest)->content);
}

void	print_smallest(t_envl *lst, t_envl **smallest, t_envl *biggest)
{
	t_envl	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->identificator, (*smallest)->identificator, ft_strlen(tmp->identificator) + 1) > 0
			&& ft_strncmp(tmp->identificator, biggest->identificator, ft_strlen(tmp->identificator) + 1) < 0)
			biggest = tmp;
		tmp = tmp->next;
	}
	printf("%s %s=%s\n", "declare -x", (char *)biggest->identificator, (char *)biggest->content);
	*smallest = biggest;
}

void	export_empty(t_mnshll *mini)
{
	t_envl	*smallest;
	t_envl	*biggest;
	int		x;

	if (*mini->envl == NULL || (*mini->envl)->identificator == NULL)
		return ;
	get_smallest_biggest(*mini->envl, &smallest, &biggest);
	x = ft_lstsize(*mini->envl) - 2;
	while (x > 0)
	{
		print_smallest(*mini->envl, &smallest, biggest);
		x--;
	}
}
