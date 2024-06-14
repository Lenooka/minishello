/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 22:14:57 by otolmach          #+#    #+#             */
/*   Updated: 2024/06/14 14:28:29 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	big_skip_quotes(char *str, char c, int x)
{
	if (str[x] && str[x] == c)
	{
		x++;
		while (str[x] && str[x] != c)
			x++;
		if (str[x] == '\0')
			return (x);
		x++;
		if (str[x] && !check_all(str, x))
			return (skip_spaces(str, x));
		else if (str[x] && str[x] == '$')
			return (skip_envar(str, x));
		else if (str[x] && check_quotes(str, x))
			return (big_skip_quotes(str, str[x], x));
	}
	return (x);
}

int	skip_spaces(char *str, int x)
{
	if (str[x] && !check_all(str, x))
	{
		while (str[x] && !check_all(str, x))
			x++;
		if (str[x] && str[x] == '$')
			return (skip_envar(str, x));
		else if (str[x] && check_quotes(str, x))
			return (big_skip_quotes(str, str[x], x));
	}
	return (x);
}

int	skip_envar(char *str, int x)
{
	if (str[x] == '$')
	{
		x++;
		if (str[x] && check_quotes(str, x))
			return (big_skip_quotes(str, str[x], x));
		else if (str[x] && !check_all(str, x))
			return (skip_spaces(str, x));
	}
	return (x);
}

int	others(char *str, int x)
{
	if (str[x] && str[x] == '|')
		x++;
	else if (str[x] == '>')
	{
		x++;
		if (str[x] && (str[x] == '>' || str[x] == '|'))
			x++;
	}
	else if (str[x] == '<')
	{
		x++;
		if (str[x] && (str[x] == '<' || str[x] == '>'))
			x++;
	}
	return (x);
}
