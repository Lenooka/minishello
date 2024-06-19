/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:22:02 by otolmach          #+#    #+#             */
/*   Updated: 2024/06/19 21:38:55 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char	*iterati(t_mnshll *minsh, char *var)
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
}*/


char *rec_list(t_envl *tmp, char *var)
{
    char *buf;

    buf = NULL;
    if (tmp == NULL)
        return (NULL);
    if (ft_strcmp(tmp->ident, var) == 0) 
	{
        buf = ft_strdup(tmp->content);
        return buf;
    }
    buf = recursive_var_iter(tmp->next, var);
    if (buf == NULL)
        free(buf);
    return buf;
}
// Call the recursive function with the initial environment list pointer

char *rec_iterati(t_mnshll *minsh, char *var)
{
    char *buf;

    if (ft_strcmp(var, "?") == 0)
    {
        buf = ft_itoa(ms->exit);
        return buf;
    }
    return (rec_list(*minsh->envl, var));
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
		vari = rec_list(minsh, tmp + 1);
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

char	*rep_var_w_val2(char *suf, char *res, char *result, char *inter)
{
    suf = ft_strdup(res + i + ft_varlen(res + i));
    free(res);
    result = ft_strjoin(inter, suf);
    free(inter);
    free(suf);
	return (result);
}

/*char	*rep_var_w_val(t_mnshll *ms, char *res, char quotes, int i)
{
	char	*var;
	char	*fix;
	char	*buffer;

	var = NULL;
	fix = NULL;
	buffer = NULL;
	fix = ft_strrepdup(res, i);
	if (!(check_quotes(res, i + 1) && !quotes))
		buffer = ft_strrepdup(res + i, ft_varlen(res + i));
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
	fix = ft_strdup(res + i + ft_varlen(res + i));
	free(var);
	free(res);
	return (rep_var_w_val2(res, fix, buffer));
}*/


char	*rep_var_w_val(t_mnshll *minsh, char *res, char quote, int i)
{
    char *var;
    char *pref;
    char *suf;
    char *inter;
    char *result;

	var = NULL
	pref = NULL;
	suf = NULL;
	result = NULL;
    pref = ft_strrepdup(res, i);
    if (!(check_quotes(input[i + 1]) && !quote))
    {
        suf = ft_strrepdup(input + index, ft_varlen(res + i));
        if (suf && ft_strcmp(suf, "$") == 0)
            var = ft_strdup(suf);
        else if (suf)
            var = iterati(minsh, suf + 1);
        free(suf);
    }
    inter = ft_strjoin(pref, var);
    free(pref);
    free(var);
	result = rep_var_w_val2(suf, res, result, inter);
    return (result);
}
