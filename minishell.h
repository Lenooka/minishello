/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:17:47 by jhuber            #+#    #+#             */
/*   Updated: 2024/03/26 18:44:29 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "LIBFTall/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include <limits.h> 
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/stat.h>
# include <stddef.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <curses.h>

extern int	g_global;

typedef struct s_envl
{
	int				equal_flag;
	int				node_flag;
	void 			*content;
	char			*identificator;
	struct s_list 	*next;
} 	t_envl;

typedef struct s_lexer
{
	char	**tokens;
} t_lexer;

typedef	struct mnshll
{
	int	command_amount;
	char	**com_array;
	int		exit;
	char	*input;
	t_envl 	**envl;
	t_lexer	*lexer;
	
} t_mnshll;

//Signals


char	*identify_env(const char *str, int c);


#endif
