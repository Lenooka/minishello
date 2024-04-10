/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_list_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:57:54 by jhuber            #+#    #+#             */
/*   Updated: 2024/04/10 13:26:25 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*

t_lexer	*init_list_of_comands(t_mnshll *minsh)
{
	t_lexer	*node;
    t_lexer	*list_com;
	int		i;

	i = 0;
	list_com = NULL;
	if (ms->cmd_count <= 0 || ms->main_arr == NULL)
		return NULL;
	while (i < minsh->command_amount && minsh->com_array[i])
	{
		node = new_node_cmdlist(minsh, i);
		if (!node)
			return NULL;
        while (minsh->com_array[i] && ft_strcmp(minsh->com_array[i], "|") != 0)
            i++;
        if (minsh->com_array && ft_strcmp(minsh->com_array[i], "|") == 0)
            i++;
        cmdlist_add_back(&cmdlist, node);
	}
    return (list_com);
}
