/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:43:24 by jhuber            #+#    #+#             */
/*   Updated: 2024/04/28 20:34:31 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_mnshll mini, char **input)
{
	int	x;
	int	check;
	char *content;

	x = 1;
	if (!input[x])
	{
		export_empty(mini);
		return ;
	}
	while (cmd_line[x])
	{
		content = ft_strdup(cmd_line[i]);
		check = check_identifier(mini, content);
		ft_export_2(mini, content, check);
		x++;
		free(content);
	}
}
