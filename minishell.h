/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 19:17:47 by jhuber            #+#    #+#             */
/*   Updated: 2024/04/25 17:27:17 by otolmach         ###   ########.fr       */
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
	char			**tokens;
	struct s_lexer	*next;
	
} t_lexer;

typedef	struct mnshll
{
	int		command_amount;
	char	**com_array;
	int		exit;
	char	*input;
	char	*heredoc_buf;
	int		fdin;
	int		fdout;
	int		fd_cmd;
	int		lenvar;
	int		rep_var_i;
	t_envl 	**envl;
	t_lexer	*list_com;
	
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
void		ft_lstadd_back(t_envl **lst, t_envl *new);
void		print_lst(t_envl **lst, int flag);
t_envl		*ft_lstlast(t_envl *lst);

//Signals
void		make_sigaction(void);
void		handler_cd(t_mnshll *mnshll);
void		check_global_end(void);
void		signal_global(int signum);
void 		handle_sigint(int signum, siginfo_t *info, void *context);


//Syntax Errors
int			syntax_error(t_mnshll *mnshll);
int			has_syntax_error(char *input);
int			report_syntax_error(char *error_message);
int			unclosed_quote(char *inp);
int			start_syntax(char *input);
int			end_syntax(char *input);
int			pipe_syntax(char *input);
int			dollar_syntax(char *input);
int			redir_syntax(char *input);
int			double_redir_syntax(char *input);
int			sucession_syntax(char *input);
int			token_syntax(char *input);
//Names need to be changed, logic of the syntax checks needs to be overworked, but for now, this works. (Should)

//Exececution
void		minishell(t_mnshll *mnshll);
void		start_procces(t_mnshll *mnshll);
void 		exit_status(t_mnshll *mnshll, pid_t pid, int com_run);
int			if_there_heredoc(t_mnshll *minsh, char **str);
void		ft_exit(t_mnshll *m);
void		parent(t_mnshll *m, int *pipe_fd, int cmrun, int pos);
void		child(t_mnshll *ms, int *pipe_fd, int cmds_run, int pos);
int			isbuilt(char *com);
void		redirect_and_close(t_mnshll *m, int fd, int op, int *pipefd);
void		exe_cutie(t_mnshll *minsh, char **array, char **new_cmd);
void		executie_ve(char *path, char **new_cmnd, char **env);
char    	**retrive_path_dir(char **env, char *s);

//Redirections
int	redir(t_mnshll *minsh, char **array, int pos, int process);
int	redirout(t_mnshll *minsh, char *check, char *filename, int process);
int	redirin(t_mnshll *minsh, char *check, char *filename, int process);
int	input_redir(t_mnshll *minsh, char *filename, int procces);
int	heredoc_redir(t_mnshll *minsh, char *filename, int procces);
int	output_redir(t_mnshll *minsh, char *filename, int process);
int	append_out_redir(t_mnshll *minsh, char *filename, int process);

//Parser
int			parser_codes(char c);
int			parser_start(t_mnshll *minsh);
int			init_fds(t_mnshll *minsh);
char		**split_tokenize(t_mnshll *minsh, char *str);
char		*ft_strncpy(char *dest, char *s, int n);
char		*ft_strndup(t_mnshll *mnshll, char *s, int n);
char		**free_arrays(char **str_tab, int i);
char		*replace_var_in_str(t_mnshll *minsh, char *str);
char		**replace_var(t_mnshll *minsh);
size_t		indx_from(t_mnshll *minsh, char *rep_res, char q, int indx);
int			get_var_len(char *str);
char		*iterati(t_mnshll *minsh, char *var);
char		**duplicate_string_array(t_mnshll *minsh, char **old_arr);
int			count_commands(char **str_tab);
t_lexer		*init_list_of_comands(t_mnshll *minsh);
char		*rep_var_w_val(t_mnshll *ms, char *result, char quotes, int str_index);

//Herdoc
int		if_there_heredoc(t_mnshll *minsh, char **str);
void	init_heredoc(t_mnshll *minsh, char *del, int num_indx);
void	heredoc_signal_handle(int signal);
int		file_des_create(t_mnshll *minsh, int here_num);
void	heredoc_child(t_mnshll *minsh, int fd, char *del);
int		create_file(t_mnshll *minsh, char *filename);
void	free_and_null(void **ptr);
void    disable_quit_signals(void);
void	heredoc_warn(char *del);
char	*hrdc_out(t_mnshll *minsh, char	*del, char *line);
int		spec_strcmp(char *s1, char *s2, char c);
int		len_un_chr(char *str, char c);

//Utilities
int			parser_codes(char c);
int			find_com_pos(char **com_array, int	pos);
int			big_skip_quotes(char *str, char c, int x);
int			little_skip_quotes(char *str, int x, int len);
int			space_tab(char *str, int x);
int			envar(char *str, int x);
int			ft_strcmp(char *s1, char *s2);
int			size_of_2d(char **arr);
char		*remove_quotes(char *str);
int			quote_amm(char *str);
void		free_all_arrays(char **str_tab);
int 		others(char *str, int x);
void		ft_lstadd_back(t_envl **lst, t_envl *new);


//FREES AND CLOSE

void	free_exit_procces(t_mnshll *minsh, char *mess);
void	close_fd(int *fd);
void	free_cmd_list(t_lexer *cmdlist);
void	dup_two_error(t_mnshll *minsh, int fd, int *pipe_fd);
int		open_error(t_mnshll *minsh, char *filename, int process);
void	free_to_main(t_mnshll *minsh);
int		open_error(t_mnshll *minsh, char *filename, int process);
void	pepe_error(t_mnshll *minsh, int *fd);
void	fork_error(t_mnshll *minsh, int *fd);
void	free_heredoc(t_mnshll *minsh);

#endif
