/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:37:16 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/24 18:31:24 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envl	*ft_lstlast(t_envl *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		else
			lst = lst->next;
	}
	return (0);
}

void	ft_lstadd_back(t_envl **lst, t_envl *new)
{
	if (ft_lstlast(*lst))
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}

void	free_env(t_envl **env)
{
	t_envl	*current;
	t_envl	*next;

	if (env == NULL || *env == NULL)
		return ;
	current = *env;
	while (current != NULL)
	{
		next = current->next;
		free(current->identificator);
		free(current->content);
		free(current);
		current = next;
	}
	free(*env);
	*env = NULL;
}

char	*envl_content_fill(const char *str, int c)
{
	int		i;
	char	*result;
	int		x;
	int		len;

	i = 0;
	x = 0;
	len = 0;
	while (str[i] != '\0' && str[i] != (char)c)
		i++;
	if (str[i] == '\0' || str[i + 1] == '\0')
		return (ft_strdup("  "));
	len = ft_strlen(str) - i;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	while (str[i] != '\0')
	{
		result[x] = str[i];
		x++;
		i++;
	}
	result[x] = '\0';
	return (result);
}

char	*identify_env(const char *str, int c)
{
	int		i;
	int		len;
	char	*result;

	i = 0;
	len = 0;
	while (str[len] != '\0' && str[len] != (char)c)
		len++;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	while (i < len)
	{
		result[i] = str[i];
		i++;
	}
	result[len] = '\0';
	return (result);
}

t_envl	*create_newnode(void *content)
{
	t_envl	*new_node;

	if (!content)
	{
		return (NULL);
	}
	new_node = malloc(sizeof(t_envl));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	if (ft_strchr(content, '=') == 0)
		new_node->equal_flag = 0;
	else
		new_node->equal_flag = 1;
	new_node->identificator = identify_env(content, '=');
	new_node->content = envl_content_fill(content, '=');
	return (new_node);
}

void	print_lst(t_envl **lst, int flag)
{
	t_envl	*tmp;
	char	*exp;

	exp = "declare -x";
	tmp = *lst;
	if (!tmp)
		return ;
	if (flag == 2)
		exp = "declare -x";
	while (tmp)
	{
		if ((tmp)->node_flag == 1 && flag == 1)
			ft_printf("%s=%s\n", (tmp)->identificator, (tmp)->content);
		else if (flag == 2)
		{
			if ((tmp)->equal_flag == 0 && ft_strcmp((tmp)->content, "  ") == 0)
				ft_printf("%s%s%s %s\n", exp, (tmp)->identificator);
			else if (ft_strcmp((tmp)->content, "  ") == 0)
				ft_printf("%s%s%s %s=\"\"\n", exp, (tmp)->identificator);
			else
				ft_printf("%s%s%s %s=\"%s\"\n", exp, \
					(tmp)->identificator, (tmp)->content);
		}
		tmp = (tmp)->next;
	}
}

t_envl	**env_list_init(char **env, int i)
{
	t_envl	**envl;
	char	*envlcontent;
	t_envl	*node;

	envl = malloc(sizeof(t_envl *));
	if (!envl)
		return (NULL);
	*envl = NULL;
	while (env[i] != NULL)
	{
		envlcontent = ft_strdup(env[i]);
		if (!envlcontent)
			return (free_env(envl), NULL);
		node = create_newnode(envlcontent);
		if (node == NULL)
			return (free_env(envl), NULL);
		if (envlcontent != NULL)
			free(envlcontent);
		node->node_flag = 1;
		ft_lstadd_back(envl, node);
		i++;
	}
	//print_lst(envl, 1);
	return (envl);
}
