/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntex_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 22:14:57 by otolmach          #+#    #+#             */
/*   Updated: 2024/03/27 19:18:49 by jhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	report_syntax_error(const char *error_message)
{
    write(2, "MiniShell: syntax error: ", 25);
    write(2, error_message, ft_strlen(error_message));
    write(2, "\n", 1);
	return (1);
}

int	has_syntax_error(const char *input) //Same name as the other function
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

int	has_syntax_error(const char *input) //Same name as the other function
{
    if (start_syntax(input) == 1) //function call to a non function? has to be made
		return (report_syntax_error("near unexpected token '|'"));
	else if (end_syntax(input) == 1) //function call to a non function? has to be made
		return (report_syntax_error("near unexpected token `newline'"));
	else if (quote_syntax(input) == 1) //function call to a non function? has to be made
		return (report_syntax_error("unclosed quote marks"));
	else if (pipe_syntax(input) == 1) //function call to a non function? has to be made
		return (report_syntax_error("near unexpected token '|'"));
    else if (dollar_syntax(input) == 1) //function call to a non function? has to be made
		return (report_syntax_error("near unexpected token '$'"));      
	else if (redir_unexpect_errors(input) == 1) //function call to a non function? has to be made
		return (1);		   
	return (0);
}

int	syntax_error(t_mnshll *mnshll)
{
	if (has_syntax_error == 1)
	{
		free(mnshll->input);
		mnshll->exit = 2;
		return (1);
	}
	return (0);
}