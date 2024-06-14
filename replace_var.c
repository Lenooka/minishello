/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:22:02 by otolmach          #+#    #+#             */
/*   Updated: 2024/06/14 14:05:27 by jhuber           ###   ########.fr       */
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
	if (!(check_quotes(rep_res, indx + 1) && !q))
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

char	*rep_var_w_val(t_mnshll *ms, char *res, char quotes, int str_index)
{
	char	*var;
	char	*fix;
	char	*buffer;

	var = NULL;
	fix = NULL;
	buffer = NULL;
	fix = ft_strrepdup(res, str_index);
	if (!(check_quotes(res, str_index + 1) && !quotes))
		buffer = ft_strrepdup(res + str_index, get_var_len(res + str_index));
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
	fix = ft_strdup(res + str_index + get_var_len(res + str_index));
	free(var);
	free(res);
	return (rep_var_w_val2(res, fix, buffer));
}
