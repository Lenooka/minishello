/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:35:05 by jhuber            #+#    #+#             */
/*   Updated: 2024/06/14 14:29:20 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_var_in_str(t_mnshll *minsh, char *str)
{
	int		indx;
	char	quote;
	char	*rep_res;

	indx = 0;
	quote = '\0';
	rep_res = ft_strdup(str);
	if (!rep_res)
		return (NULL);
	while (rep_res && rep_res[indx])
	{
		if (!quote && check_quotes(rep_res, indx))
			quote = rep_res[indx];
		else if (quote && rep_res[indx] == quote)
			quote = '\0';
		if (rep_res[indx] == '$' && quote != '\'')    //&& quote != '\"')
		{
			minsh->lenvar = indx_from(minsh, rep_res, quote, indx);
			rep_res = rep_var_w_val(minsh, rep_res, quote, indx);
			indx += minsh->lenvar;
		}
		indx++;
	}
	return (rep_res);
}

char	**replace_var(t_mnshll *minsh)
{
	char	**rep_arr;
	char	*rep_res;
	int		i;

	i = 0;
	rep_res = NULL;
	rep_arr = ft_calloc(sizeof(char *), size_of_2d(minsh->com_array) + 1);
	if (!rep_arr)
		return (NULL);
	while (minsh->com_array[i])
	{
		if (!ft_strchr(minsh->com_array[i], '$'))
		{
			rep_arr[minsh->rep_var_i] = ft_strdup(minsh->com_array[i]);
			minsh->rep_var_i++;
			i++;
			continue ;
		}
		rep_res = replace_var_in_str(minsh, minsh->com_array[i++]);
		if (rep_res && rep_res[0])
			rep_arr[minsh->rep_var_i++] = rep_res;
	}
	rep_arr[minsh->rep_var_i] = NULL;
	free_all_arrays(minsh->com_array);
	return (rep_arr);
}
