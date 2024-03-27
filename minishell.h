/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhuber <jhuber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:17:47 by jhuber            #+#    #+#             */
/*   Updated: 2024/03/27 19:22:44 by jhuber           ###   ########.fr       */
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

//main function
int			main(int arc, char **arv, char **env);

//minishell struct initiation
t_mnshll	*mnshll_init(t_mnshll *mnshll, char **env);

//environment struct initiation
t_envl		**env_list_init(char **env, int i);
t_envl		*create_newnode(void *content);
char		*identify_env(const char *str, int c);
char		*envl_content_fill(const char *str, int c);
void		free_env(t_envl **env);

//Signals
void		make_sigaction(void);
void		handler_cd(t_mnshll *mnshll);
void		check_global_end(void);
void		signal_global(int signum);
void		handle_sigint(int signum);

//Syntax Errors
int			syntax_error(t_mnshll *mnshll);
int			has_syntax_error(const char *input);
int			report_syntax_error(const char *error_message);

//Exececution
void		start_procces(t_mnshll *mnshll);

//Utilities
int			find_com_pos(char **com_array, int	pos);

#endif
