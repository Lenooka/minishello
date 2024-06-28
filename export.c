/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:43:24 by jhuber            #+#    #+#             */
/*   Updated: 2024/06/24 22:36:34 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
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
	if (!input[1])
		export_empty(mini);
	else
	{
		while (input[x])
		{
			content = ft_strdup(input[x]);
			check = check_identifier(mini, content);
			ft_export_2(mini, content, check);
			x++;
			free(content);
		}
	}
}
*/

char	*get_content(char *str)
{
	int		x;
	int		y;
	char	*content;

	x = 0;
	y = ft_strlen(str);
	while (str[x])
	{
		if (str[x] == '=')
			break ;
		x++;
	}
	content = (char *)malloc(sizeof(char) * (y - x + 1));
	if (!content)
		return (NULL);
	y = 0;
	x++;
	while (str[x])
	{
		content[y] = str[x];
		x++;
		y++;
	}
	content[y] = '\0';
	return (content);
}

int	check_equal_flag(char *str)
{
	int	x;
	int	check;

	x = 0;
	check = 0;
	while (str[x])
	{
		if (str[x] == '=')
		{
			check = 1;
			break ;
		}
		x++;
	}
	if (check)
	{
		if (str[x + 1] == '\0')
			return (0);
		return (1);
	}
	return (0);
}

char	*get_identificator(char *str, t_mnshll *mini)
{
	int	x;
	int	check;

	if (ft_strcmp(str, "_") == 0)
		return (NULL);
	x = 0;
	check = 0;
	if ((str[x] <= '9' && str[x] >= '0') || str[x] == '=')
		check = 1;
	while (str[x] != '=' && str[x])
	{
		if (!((str[x] >= 'a' && str[x] <= 'z') || (str[x] >= '0' && str[x] <= '9')
			|| (str[x] >= 'A' && str[x] <= 'Z') || str[x] == '_'))
			check = 1;
		x++;
	}
	if (check)
	{
		error_msg(mini, "Not a valid Identifier", 1, "Export: ");
		mini->exit = 1;
		return (NULL);
	}
	if (!str[x])
		return (ft_strdup(str));
	return (ft_strndup(mini, str, x));		//if the content is off take the - 1 off
}

void	make_new_node(char *str, t_mnshll *mini)
{
	t_envl	*new_node;

	new_node = malloc(sizeof(t_envl));
	new_node->identificator = get_identificator(str, mini);
	if (new_node->identificator == NULL)
		return ;
	if (check_equal_flag(str))
	{
		new_node->content = get_content(str);
		if (!new_node->content)
			return ;
		new_node->equal_flag = 1;
	}
	else
	{
		new_node->content = ft_strdup(" ");
		new_node->equal_flag = 0;
	}
	ft_lstadd_front(mini->envl, new_node);
}

void	ft_export(t_mnshll *mini, char **input)
{
	int		x;

	x = 1;
	if (!input[1])
		export_empty(mini);
	else
	{
		while (input[x])
		{
			make_new_node(input[x], mini);
			x++;
		}
	}
}
