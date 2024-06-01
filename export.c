/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:43:24 by jhuber            #+#    #+#             */
/*   Updated: 2024/06/01 16:53:42 by otolmach         ###   ########.fr       */
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

int	find_ident(t_envl **env, char *ident, char *new_cont, int flag)
{
	t_envl	*tmp;

	tmp = *env;
	if (!tmp)
		perror("export");
	while (tmp)
	{
		if (ft_strcmp((char *)(tmp)->identificator, ident) == 0)
		{
			if (flag == 2 && (tmp)->node_flag == 1)
				return (1);
			if (flag == 1 && (tmp)->node_flag == 2)
			{
				(tmp)->node_flag = 1;
				(tmp)->equal_flag = 1;
			}
			free((tmp)->content);
			(tmp)->content = ft_strdup(new_cont);
			free(new_cont);
			free(ident);
			return (2);
		}
		tmp = (tmp)->next;
	}
	return (0);
}

int	check_identifier(t_mnshll *mini, char *content)
{
	char	*ident;
	char	*new_con;
	int		flag;

	flag = 0;
	new_con = get_cont(content, '=');
	ident = get_ident(content, '=');
	if (valid_ident(ident) == 1)
		flag = get_flag(mini, ident, new_con, content);
	else if (valid_ident(ident) == 0)
	{
		error_msg(mini, "not a valid identifier", 1, "export");
		mini->exit = 1;
	}
	if (flag == 1 || flag == 3 || flag == 0)
	{
		free(ident);
		free(new_con);
	}
	return (flag);
}

void	ft_export_2(t_mnshll *mini, char *content, int check)
{
	t_envl	*new;

	if (check == 1)
	{
		new = ft_envnew(content);
		new->node_flag = 1;
		new->equal_flag = 1;
		ft_lstadd_front(mini->envl, new);
	}
	if (check == 3)
	{
		new = ft_envnew(content);
		new->node_flag = 2;
		new->equal_flag = 0;
		ft_lstadd_front(mini->envl, new);
	}
}

void	ft_export(t_mnshll *mini, char **input)
{
	int		x;
	int		check;
	char	*content;

	x = 1;
	if (!input[x])
	{
		export_empty(mini);
		return ;
	}
	while (input[x])
	{
		content = ft_strdup(input[x]);
		check = check_identifier(mini, content);
		ft_export_2(mini, content, check);
		x++;
		free(content);
	}
}
