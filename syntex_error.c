/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntex_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 22:14:57 by otolmach          #+#    #+#             */
/*   Updated: 2024/06/10 15:10:40 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_message(char *error_message)
{
	write(2, "error: syntax error ", 20);
	write(2, error_message, ft_strlen(error_message));
	write(2, "\n", 1);
	return (1);
}

int	other_syntax_errors(char *input)
{
	int	x;
	int len;

	len = ft_strlen(input) - 1;
	x = check_redir_syntax(input);
	if (x == 1)
		return (syntax_message("near unexpected token `|'"));
	if (x == 2)
		return (syntax_message("near unexpected token `newline'"));
	if (x == 3)
		return (syntax_message("near unexpected token `<'"));
	else if (double_redir_syntax(input) == 1)
		return (syntax_message("near unexpected token `|'"));
	else if (sucession_syntax(input, len) == 1)
		return (syntax_message("near unexpected token `|'"));
	else if (token_syntax(input) == 1)
		return (syntax_message("near unexpected token `&();'"));
	return (0);
}

int	has_syntax_error(char *input)
{
	if (start_syntax(input) == 1)
		return (syntax_message("near unexpected token `|'"));
	else if (end_syntax(input) == 1)
		return (syntax_message("near unexpected token `newline'"));
	else if (unclosed_quote(input) == 1)
		return (syntax_message("unclosed quote marks"));
	else if (check_pipe_syntax(input) == 1)
		return (syntax_message("near unexpected token '|'"));
	else if (check_dollar_syntax(input) == 1)
		return (syntax_message("near unexpected token '$'"));
	else if (other_syntax_errors(input) == 1)
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
