/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_empty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:51:25 by jhuber            #+#    #+#             */
/*   Updated: 2024/06/24 19:49:43 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if ((*smallest)->equal_flag)
		printf("%s %s=\"%s\"\n", "declare -x", (char *)(*smallest)->identificator, (char *)(*smallest)->content);
	else
		printf("%s %s\"%s\"\n", "declare -x", (char *)(*smallest)->identificator, (char *)(*smallest)->content);
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
	if (biggest->equal_flag)
		printf("%s %s=\"%s\"\n", "declare -x", (char *)biggest->identificator, (char *)biggest->content);
	else
		printf("%s %s\"%s\"\n", "declare -x", (char *)biggest->identificator, (char *)biggest->content);
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
