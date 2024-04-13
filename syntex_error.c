/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntex_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 22:14:57 by otolmach          #+#    #+#             */
/*   Updated: 2024/04/13 15:01:51 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	report_syntax_error(char *error_message)
{
	write(2, "MiniShell: syntax error: ", 25);
	write(2, error_message, ft_strlen(error_message));
	write(2, "\n", 1);
	return (1);
}

int	redir_unexpect_errors(char *input)
{
	if (redir_syntax(input) == 1) //function call to a non function? has to be made
		return (1);
	else if (double_redir_syntax(input) == 1) //function call to a non function? has to be made
		return (1);
	else if (sucession_syntax(input) == 1) //function call to a non function? has to be made 
		return (1);
	else if (token_syntax(input) == 1) //function call to a non function? has to be made
		return (1);
	return (0);
}

int	has_syntax_error(char *input)
{
	if (start_syntax(input) == 1) //function call to a non function? has to be made
		return (report_syntax_error("near unexpected token '|'"));
	else if (end_syntax(input) == 1) //function call to a non function? has to be made
		return (report_syntax_error("near unexpected token `newline'"));
	else if (unclosed_quote(input) == 1)
		return (report_syntax_error("unclosed quote marks"));
	else if (pipe_syntax(input) == 1) //function call to a non function? has to be made
		return (report_syntax_error("near unexpected token '|'"));
	else if (dollar_syntax(input) == 1) //function call to a non function? has to be made
		return (report_syntax_error("near unexpected token '$'"));
	else if (redir_unexpect_errors(input) == 1) //function call to a non function? has to be made ☝️🤓
		return (1);
	return (0);
}

int	syntax_error(t_mnshll *mnshll)
{
	if (has_syntax_error(mnshll->input) == 1)
	{
		free(mnshll->input);
		mnshll->exit = 2;
		return (1);
	}
	return (0);
}
