/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocheck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:22:07 by olena             #+#    #+#             */
/*   Updated: 2024/06/15 19:09:34 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*var_iter(t_mnshll *ms, char *var)
{
	char	*buf;
	t_envl	*tmp;

	if (ft_strcmp(var, "?") == 0)
	{
		buf = ft_itoa(ms->exit);
		return (buf);
	}
	tmp = *ms->envl;
	while (tmp)
	{
		if (ft_strcmp((tmp)->identificator, var) == 0)
			buf = ft_strdup((tmp)->content);
		else
			buf = NULL;
		if (buf)
			return (buf);
		tmp = tmp->next;
		free(buf);
	}
	return (NULL);
}

// equivalent to `env | grep va
char	*var_str(t_envl *env, char *var)
{
	t_envl	*tmp;

	tmp = env;
	while (tmp->content)
	{
		if (ft_strncmp((char *)tmp->content, var, ft_strlen(var)) == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	return (tmp->content);
}


int	parser_op(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	if (c == '<' || c == '>' || c == '|')
		return (2);
	if (c == '\'' || c == '\"')
		return (3);
	if (c == '$')
		return (4);
	return (0);
}

int	get_var(char *str)
{
	int	i;

	i = 0;
	if (parser_op(str[i]) != 4)
		return (0);
	i++;
	if (str[i] && (str[i] == '?' || ft_isdigit(str[i])))
		return (2);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

// This function replaces one environment variable with its value
char	*replace_var(t_mnshll *ms, char *result, char quotes, int str_index)
{
	char	*var;
	char	*fix;
	char	*buffer;

	var = NULL;
	fix = NULL;
	buffer = NULL;
	fix = ft_strndup(ms, result, str_index);
	if (!(parser_op(result[str_index + 1]) == 3 && !quotes))
		buffer = ft_strndup(ms, result + str_index, \
		get_var(result + str_index));
	if (buffer && ft_strcmp(buffer, "$") == 0)
		var = ft_strdup(buffer);
	else if (buffer)
		var = iterati(ms, buffer + 1);
	free(buffer);
	buffer = ft_strjoin(fix, var);
	free(fix);
	fix = ft_strdup(result + str_index + ft_varlen(result + str_index));
	free(var);
	free(result);
	result = ft_strjoin(buffer, fix);
	free(buffer);
	free(fix);
	return (result);
}

size_t	get_new_index(t_mnshll *ms, char *result, char quotes, int str_index)
{
	char	*var;
	char	*buffer;
	int		new_index;

	var = NULL;
	buffer = NULL;
	new_index = 0;
	if (!(parser_op(result[str_index + 1]) == 3 && !quotes))
		buffer = ft_strndup(ms, result + str_index, \
		get_var(result + str_index));
	if (buffer && ft_strcmp(buffer, "$") == 0)
		var = ft_strdup(buffer);
	else if (buffer)
		var = var_iter(ms, buffer + 1);
	new_index = ft_strlen(var);
	free(buffer);
	free(var);
	return (new_index);
}


char	*replace_str(t_mnshll *ms, char *str)
{
	int		var_len;
	char	*result;
	char	quotes;
	int		str_index;

	var_len = 0;
	quotes = '\0';
	str_index = 0;
	result = ft_strdup(str);
	while (result && result[str_index])
	{
		if (!quotes && parser_op(result[str_index]) == 3)
			quotes = result[str_index];
		else if (quotes && result[str_index] == quotes)
			quotes = '\0';
		if (result[str_index] == '$' && quotes != '\'')
		{
			var_len = get_new_index(ms, result, quotes, str_index);
			result = replace_var(ms, result, quotes, str_index);
			str_index += var_len - 1;
		}
		str_index++;
	}
	return (result);
}

void	free_hdoc(t_mnshll *ms)
{

	close(0);
	close(1);
	if (ms->fdin != -1)
		close(ms->fdin);
	if (ms->fdout != -1)
		close(ms->fdout);
	rl_clear_history();
	exit (1);
}
int	strlen_chr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int	strcmp_nochr(char *s1, char *s2, char c)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]) && i < strlen_chr(s2, c) - 1)
		i++;
	if (i < (int)ft_strlen(s1) - 1)
		return (1);
	return (s1[i] - s2[i]);
}

void	change_terminal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	create_file(t_mnshll *ms, char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		open_error(ms, filename, 1);
	free(filename);
	return (fd);
}

char	*create_filename(int here_num)
{
	int		i;
	char	*buf;
	char	*filename;

	i = 0;
	buf = NULL;
	filename = ft_strdup("/tmp/tmpxxx");
	while (i < here_num)
	{
		buf = ft_strdup(filename);
		free(filename);
		filename = ft_strjoin(buf, "x");
		free(buf);
		i++;
	}
	return (filename);
}

void	heredoc_signal(int signum)
{
	if (signum == SIGINT)
	{
		g_global = SIGINT;
		printf("\n");
		close(STDIN_FILENO);
	}
}


char	*heredoc_output(t_mnshll *ms, char *limiter, char *line)
{
	char	*buf;

	buf = remove_quotes(limiter);
	if (g_global == SIGINT || !line || spec_strcmp(buf, line, '\n') == 0)
	{
		free(buf);
		return (NULL);
	}
	free(buf);
	if (!ft_strchr(limiter, '\'') && !ft_strchr(limiter, '\"'))
		buf = replace_var_in_str(ms, line);
	else
		buf = ft_strdup(line);
	return (buf);
}

void	heredoc_child(t_mnshll *ms, char *filename, char *limiter)
{
	char	*output;
	char	*line;
	int		fd;

	line = NULL;
	fd = create_file(ms, filename);
	while (1)
	{
		change_terminal();
		line = readline("> ");
		if (g_global == SIGINT)
			ms->exit = 128 + SIGINT;
		else if (!line)
			heredoc_warn(limiter);
		output = hrdc_out(ms, limiter, line);
		if (!output)
			break ;
		free(line);
		ft_putendl_fd(output, fd);
		free(output);
	}
	if (line)
		free(line);
	close(fd);
	free_heredoc(ms, fd);
}

char	*heredoc(t_mnshll *ms, char *limiter, int here_num)
{
	char	*filename;
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	filename = create_filename(here_num);
	pid = fork();
	if (pid < 0)
		fork_error(ms, NULL);
	if (pid == 0)
	{
		signal(SIGINT, heredoc_signal);
		heredoc_child(ms, filename, limiter);
	}
	else
	{
		wait(&status);
		if (pid != -1 && WIFEXITED(status) && WEXITSTATUS(status) == (128 + \
			SIGINT))
		{
			g_global = SIGINT;
			unlink(filename);
		}
	}
	return (filename);
}

int	init_heredoc(t_mnshll *ms, char **main_arr)
{
	int		index;
	char	*buf;

	index = 0;
	if (!main_arr || !main_arr[0] || !main_arr[0][0])
		return (0);
	while (main_arr[index])
	{
		if (ft_strcmp(main_arr[index], "<<") == 0)
		{
			buf = heredoc(ms, main_arr[index + 1], index);
			free(main_arr[index + 1]);
			main_arr[index + 1] = ft_strdup(buf);
			free(buf);
			if (g_global == SIGINT)
			{
				g_global = 0;
				return (1);
			}
			index += 2;
		}
		else
			index++;
	}
	return (0);
}