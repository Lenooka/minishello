/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:17:47 by jhuber            #+#    #+#             */
/*   Updated: 2024/04/09 13:16:21 by otolmach         ###   ########.fr       */
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
	struct s_envl 	*next;
} 	t_envl;

typedef struct s_lexer
{
	char	**tokens;
} t_lexer;

typedef	struct mnshll
{
	int		command_amount;
	char	**com_array;
	int		exit;
	char	*input;
	char	*heredoc_buf:
	int		fdin;
	int		fdout;
	int		fd_cmd;
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
int			unclosed_quote(char *inp);
int			start_syntax(char *input);
int			end_syntax(char *input);
int			pipe_syntax(char *input);
int			dollar_syntax(char *input);

//Exececution
void		minishell(t_mnshll *mnshll);
void		start_procces(t_mnshll *mnshll);
void 		exit_status(t_mnshll *mnshll, pid_t pid, int com_run);
int			if_there_heredoc(t_mnshll *minsh, char **str);
//Parser
int			parser_codes(char c);
int			parser_start(t_mnshll *minsh);
int			init_fds(t_mnshll *minsh);
char		**split_tokenize(t_mnshll *minsh, char *str);
char		*ft_strncpy(char *dest, char *s, int n);
char		*ft_strndup(t_mnshll *mnshll, char *s, int n);
void		free_arrays(char **str_tab, int i);

//Utilities
int			parser_codes(char c);
int			find_com_pos(char **com_array, int	pos);
int			skipping_quotes(char *str, char c, int x);
int			skipping_quotes(char *str, char c, int x);
int			space_tab(char *str, int x);
int			envar(char *str, int x);
int			ft_strcmp(char *s1, char *s2);

#endif
