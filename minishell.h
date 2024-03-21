/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:17:47 by jhuber            #+#    #+#             */
/*   Updated: 2024/03/21 18:00:55 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "LIBFTall/libft.h"
# include <sys/stat.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <stddef.h>

typedef struct s_lexer
{
	char	*input;
	char	**tokens;
} t_lexer;

typedef	struct mnshll
{
	int	command_amount;
	char	**com_array;
	
} t_mnshll;


#endif