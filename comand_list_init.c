/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_list_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:57:54 by jhuber            #+#    #+#             */
/*   Updated: 2024/04/11 12:30:29 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_back(t_lexer **lst, t_lexer*new)
{
	t_lexer *last;

	last = *lst;
    if (!*lst)
    {
        *lst = new;
        return;
    }
    while (last->next)
    {
        last = last->next;
    }
    last->next = new;
}

char	**tokenize_commands(t_mnshll *minsh, char **arr, int pos, int argc)
{
	int		i;
	char	**res;

	int = 0;
	res = malloc(sizeof(char *) * (argc + 1));
	if (!res)
		//error exit malloc fail
	while (arr[pos] && i < argc)
	{
		if (arr[pos][0] == '\0')
		{
			pos++;
			continue;
		}
		if (arr[pos] && (ft_strcmp(arr[pos], ">") == 0 \
			|| ft_strcmp(arr[pos], ">>") == 0 || ft_strcmp(arr[pos], "<") == 0 \
			|| ft_strcmp(arr[pos], "<<") == 0))
			pos += 2;
		else if (ft_strcmp(arr[pos], "|") == 0)
			break ;
		else
			res[i++] = arr[pos++];
	}
	res[i] = NULL;
	return (res);
}

int	count_argument_f_cmnd(char **array, int indx)
{
	int	pos;
	int	count;

	pos = indx;
	count = 0;
	while (array[pos] != '\0' && ft_strchr(array[pos], "|") != 0)
	{
		if (array[pos][0] == '\0')
		{
			pos++;
			continue;
		}
		if ((ft_strcmp(arr[i], ">") == 0 || ft_strcmp(arr[i], ">>") == 0 ||
            ft_strcmp(arr[i], "<") == 0 || ft_strcmp(arr[i], "<<") == 0))
		{
			pos += 2;
		}
		else
		{
			count++;
			pos++;
		}
	}
	return (count);
}

t_lexer	*new_node_cmdlist(t_mnshll *m, int indx)
{
	t_lexer	*list_com;
	int		arg_count;

	
	list_com = malloc((t_lexer));
	if (!list_com)
		//error exit malloc error
	arg_count = count_argument_f_cmnd(m->com_array, indx);
	list_com->tokens = tokenize_commands(m, m->com_array, indx, arg_count);
	list_com->next = NULL;
	return (list_com);
}

t_lexer	*init_list_of_comands(t_mnshll *minsh)
{
	t_lexer		*node;
	t_lexer		*list_com;
	int			i;

	i = 0;
	list_com = NULL;
	if (ms->cmd_count <= 0 || ms->main_arr == NULL)
		return (NULL);
	while (i < minsh->command_amount && minsh->com_array[i])
	{
		node = new_node_cmdlist(minsh, i);
		if (!node)
			return (NULL);
		while (minsh->com_array[i] && ft_strcmp(minsh->com_array[i], "|") != 0)
			i++;
		if (minsh->com_array && ft_strcmp(minsh->com_array[i], "|") == 0)
			i++;
		add_new_back(&list_com, node);
	}
	return (list_com);
}