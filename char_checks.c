/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:19:35 by jhuber            #+#    #+#             */
/*   Updated: 2024/06/14 14:31:00 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_quotes(char *str, int x)
{
	if (str[x] == '\"' || str[x] == '\'')
		return (1);
	return (0);
}

int check_redir_pipe(char *str, int x)
{
	if (str[x] == '|' || str[x] == '>' || str[x] == '<')
		return (1);
	return (0);
}

int check_space_tabs(char *str, int x)
{
	if (str[x] == ' ' || str[x] == '\t')
		return (1);
	return (0);
}

int check_dollar(char *str, int x)
{
	if (str[x] == '$')
		return (1);
	return (0);
}

int check_all(char *str, int x)
{
	int y;

	y = 0;
	y += check_quotes(str, x);
	y += check_redir_pipe(str, x);
	y += check_space_tabs(str, x);
	y += check_dollar(str, x);
	return (y);
}
