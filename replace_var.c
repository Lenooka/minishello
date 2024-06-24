/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:22:02 by otolmach          #+#    #+#             */
/*   Updated: 2024/06/24 15:28:22 by otolmach         ###   ########.fr       */
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
		varlena = ft_varlen(rep_res + indx);
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

char	*rep_var_w_val2(char *result, char *pref, char *buffer)
{
	if (buffer && pref)
		result = ft_strjoin(buffer, pref);
	else
		result = NULL;
	free(buffer);
	free(pref);
	return (result);
}

char	*var_assing(t_mnshll *minsh, char *var, char *buffer)
{
	if (buffer && ft_strcmp(buffer, "$") == 0)
	{
		var = ft_strdup(buffer);
		return (var);
	}
	else if (buffer)
	{
		var = iterati(minsh, buffer + 1);
		return (var);
	}
	return (var);
}

char	*rep_var_w_val(t_mnshll *minsh, char *res, char quotes, int i)
{
	char	*var;
	char	*pref;
	char	*buffer;

	var = NULL;
	pref = NULL;
	buffer = NULL;
	pref = ft_strrepdup(res, i);
	if (!(check_quotes(res, i + 1) && !quotes))
		buffer = ft_strrepdup(res + i, ft_varlen(res + i));
	var = var_assing(minsh, var, buffer);
	free(buffer);
	if (pref && var)
		buffer = ft_strjoin(pref, var);
	else
		buffer = NULL;
	free(pref);
	pref = ft_strdup(res + i + ft_varlen(res + i));
	free(var);
	free(res);
	return (rep_var_w_val2(res, pref, buffer));
}
