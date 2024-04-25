/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:03:20 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/25 14:53:04 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_global = 0;

/*if envl fails I free it inside the init*/

int	main(int arc, char **arv, char **env)
{
	t_mnshll	*mnshll;

	if (arc == 1 && arv[1] == NULL)
	{
		mnshll = NULL;
		mnshll = mnshll_init(mnshll, env);
		if (mnshll == NULL)
			return (0);
		while (1)
		{
			make_sigaction();
			mnshll->input = readline("Minishell <3 : ");
			if (mnshll->input == NULL)
				break ;
			if (ft_strlen(mnshll->input) != 0 && mnshll->input[0] != '\0')
				add_history(mnshll->input);
			if (syntax_error(mnshll) == 1 && mnshll->input)
				continue ;
			else if (parser_start(mnshll) != 1)
				minishell(mnshll);
		}
		free_to_main(mnshll);
	}
	return (0);
}
