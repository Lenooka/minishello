/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olena <olena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:10:26 by jhuber            #+#    #+#             */
/*   Updated: 2024/04/04 22:16:48 by olena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser_codes(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	if (c == '<' || c == '>' || c == '|')
		return (2);
	if (c == ' ' || c == '\t')
		return (3);
	if (c == '$')
		return (4);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int		i;
	char	a;
	char	b;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	a = s1[i];
	b = s2[i];
	return (a - b);
}

int skipping_quotes(?)