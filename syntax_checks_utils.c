/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checks_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 06:22:38 by jhuber            #+#    #+#             */
/*   Updated: 2024/06/10 06:30:10 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_squotes(char *str, int x)
{
	if (str[x] == '\'')
		x++;
	else
		return (0);
	while (str[x] && str[x] != '\'')
			x++;
	if (str[x] == '\0')
		return (1);
	x++;
	return (0);
}