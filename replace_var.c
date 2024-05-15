/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:22:02 by otolmach          #+#    #+#             */
/*   Updated: 2024/05/15 16:56:51 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*iterati(t_mnshll *minsh, char *var)
{
	char	*buf;
	t_envl	*tmp;


	if (ft_strcmp(var, "?") == 0)
	{
		buf = ft_itoa(minsh->exit);
		return (buf);
	}
	tmp = *minsh->envl;
	while (tmp)
	{
		if (ft_strcmp((tmp)->identificator, var) == 0)
			buf = ft_strdup((tmp)->content);
		else
			buf = NULL;
		if (buf)
			return (buf);
		tmp = tmp->next;
		free(buf);
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
	if (vari)
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
char	*ft_strrepdup(char *str, int len)
{
	char	*res;

	res = malloc(sizeof(char) * len + 1);
	if (!res)
	{
		printf("Minishell: Malloc error!\n");
		return (NULL);
	}
	ft_strlcpy(res, str, len + 1);
	return (res);
}
char	*rep_var_w_val2(char *result, char *fix, char *buffer)
{
	if (buffer && fix)
		result = ft_strjoin(buffer, fix);
	else
		result = NULL;
	free(buffer);
	free(fix);
	return (result);
}


char	*rep_var_w_val(t_mnshll *ms, char *result, char quotes, int str_index)
{
	char	*var;
	char	*fix;
	char	*buffer;

	var = NULL;
	fix = NULL;
	buffer = NULL;
	fix = ft_strrepdup(result, str_index);
	if (!(parser_codes(result[str_index + 1]) == 1 && !quotes))
		buffer = ft_strrepdup(result + str_index, get_var_len(result + str_index));
	if (buffer && ft_strcmp(buffer, "$") == 0)
		var = ft_strdup(buffer);
	else if (buffer)
		var = iterati(ms, buffer + 1);
	free(buffer);
	if (fix && var)
		buffer = ft_strjoin(fix, var);
	else
		buffer = NULL;
	free(fix);
	fix = ft_strdup(result + str_index + get_var_len(result + str_index));
	free(var);
	free(result);
	return (rep_var_w_val2(result, fix, buffer));
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
		if (!quote && parser_codes(rep_res[indx]) == 1)
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
