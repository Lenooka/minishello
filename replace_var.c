/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:22:02 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/15 18:48:54 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
  quote == 1m / 3n
  redir&&pip == 2
  tab space == 3m / 1n
  $ = 4
*/

char	*iterati(t_mnshll *minsh, char *var)
{
	char	*buf;
	t_envl	*tmp;

	buf = NULL;
	if (ft_strcmp(var, "?") == 0)
	{
		if (minsh->exit == 0)
			return ("0");
		buf = ft_itoa(minsh->exit);
		return (buf);
	}
	tmp = *minsh->envl;
	while (tmp)
	{
		if (ft_strcmp((tmp)->identificator, var) == 0)
		{
			buf = ft_strdup((tmp)->content);
			return (buf);
		}
		tmp = tmp->next;
	}
	return (NULL);
}


size_t	indx_from(t_mnshll *minsh, char *rep_res, char q, int indx)
{
	char	*vari;
	char	*tmp;
	int		indx_from;
	int		varlena;

	vari = NULL;
	tmp = NULL;
	indx_from = 0;
	if (!(parser_codes(rep_res[indx + 1]) == 1 && !q))
	{
		varlena = get_var_len(rep_res + indx);
		tmp = ft_strndup(minsh, rep_res + indx, varlena);
	}
	if (tmp && ft_strcmp(tmp, "$") == 0)
		vari = iterati(minsh, tmp + 1);
	indx_from = ft_strlen(vari);
	free(tmp);
	free(vari);
	return (indx_from);
}

/*
rep env var with value
it works OMG
is it????????
yes?
yes...
*/
char	*rep_var_w_val(t_mnshll *ms, char *result, char quotes, int str_index)
{
	char	*var;
	char	*fix;
	char	*buffer;

	var = NULL;
	fix = NULL;
	buffer = NULL;
	fix = ft_strndup(ms, result, str_index);
	if (!(parser_codes(result[str_index + 1]) == 3 && !quotes))
		buffer = ft_strndup(ms, result + str_index, get_var_len(result + str_index));
	if (buffer && ft_strcmp(buffer, "$") == 0)
		var = ft_strdup(buffer);
	else if (buffer)
		var = iterati(ms, buffer + 1);
	free(buffer);
	buffer = ft_strjoin(fix, var);
	free(fix);
	fix = ft_strdup(result + str_index + get_var_len(result + str_index));
	free(var);
	free(result);
	result = ft_strjoin(buffer, fix);
	free(buffer);
	free(fix);
	return (result);
}

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
		if (!quote && parser_codes(rep_res[indx]) == 3)
			quote = rep_res[indx];
		else if (quote && rep_res[indx] == quote)
			quote = '\0';
		if (rep_res[indx] == '$' && quote != '\'')
		{
			minsh->lenvar = indx_from(minsh, rep_res, quote, indx);
			rep_res = replace_vari(minsh, rep_res, quote, indx);
			indx += minsh->lenvar - 1;
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
	return (rep_arr);
}
