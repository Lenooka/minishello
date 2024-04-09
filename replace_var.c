/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:22:02 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/09 17:42:17 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
  quote == 1m / 3n
  redir&&pip == 2
  tab space == 3m / 1n
  $ = 4
*/

char	*replace_var_in_str(t_mnshll *minsh, char *str)
{
	int		indx;
	int		len;
	char	quote;
	char	*rep_res;

	indx = 0;
	rep_res = ft_strdup(str);
	if (!rep_res)
		return (NULL);
	while (rep_res && rep_res[indx])
	{
		
	}
}

char	**replace_var(t_mnshll *minsh)
{
	char	**rep_arr;
	char	*rep_res;
	int		i;

	i = 0;
	rep_res = NULL;
	rep_arr = ft_calloc((sizeof(char *), size_of_2d(minsh->com_array)));
	if (!rep_arr)
		return (NULL);
	while (minsh->com_array[i])
	{
		if (!ft_strchr(minsh->com_array[i], '$'))
		{
			rep_arr[minsh->rep_var_i] = ft_strchr(minsh->com_array[i]);
			minsh->rep_var_i++;
			i++;
			continue ;
		}
		rep_res = replace_var_in_str(minsh, minsh->com_array[i++]);
		if (rep_res && rep_res[0])
			rep_arr[minsh->rep_var_i++] = ft_strdup(rep_res);
		free(rep_res);
	}
	rep_arr[minsh->rep_var_i] = NULL;
	return (rep_arr);
}
