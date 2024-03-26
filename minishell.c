/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otolmach <otolmach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:03:20 by otolmach          #+#    #+#             */
/*   Updated: 2024/03/26 15:11:19 by otolmach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_com_pos(char **com_array, int	pos)
{
	//find position untill "|"
}

void exit_status(t_mnshll *mnshll, pid_t pid, int com_run) 
{
    int status;
    int last_status = 0;
    int any_command_failed = 0;

    if (mnshll->command_amount == 1) // and is builtin 
	{
        wait(&status);
		//reset file descriptors
        return;
    }
    while (com_run > 0) 
	{
        wait(&status);
        if (pid != -1 && WIFEXITED(status))  //if child evaluate properly
		{
            last_status = WEXITSTATUS(status); // gets exit status and updates last_status
            //if (last_status == 127) 
               // any_command_failed = 1;
        } 
		else if (pid != -1 && WIFSIGNALED(status)) //checking if process term with signal 
		{
            g_global = WTERMSIG(status); // gets exit status of the signal
            //any_command_failed = 1; //command failed due to a signal not sure about this one
        }
        com_run--;
    }
   // if (any_command_failed == 1)
       /// mnshll->exit = 127; this is is not correct most probably
        mnshll->exit = last_status;
	//reset file descriptors
}



void    start_procces(t_mnshll *mnshll)
{
    int     com_run;
    int     pipefd[2];
    pid_t   pid;
    int     position;

    com_run = 0;
	position = 0;
    while (com_run < mnshll->command_amount) //the amount of the commands from parser
    {
		if (pipe(pipefd) == -1)
		{
			//free_error
		}
		pid = fork();
		if (pid < 0)
			//free_error
		if (pid != 0)
			position = 0;
			//parrent
		else
			position = 0;
            //child
		position = find_com_pos(mnshll->com_array, position);
    }
	exit_status(mnshll, pid, com_run);
}



void free_env(t_envl **env) 
{
	t_envl *current;
	t_envl *next;
 
	if (env == NULL || *env == NULL) 
	{
        return ; 
    }
    current = *env;
    while (current != NULL) 
	{
        next = current->next;
        free(current->identificator);
        free(current->content);
        free(current);
        current = next;
    }
    free(env);
}


t_envl	**env_list_init(char **env, int i)
{
	t_envl	**envl;
	char	*envlcontent;
	t_envl	*node;

	envl = malloc(sizeof(t_envl *));
	if (!envl)
		return (NULL);
	*envl = NULL;
	while (env[i] != NULL)
	{
		envlcontent = ft_strdup(env[i]);
		if (!envlcontent)
			return (free_env(envl), NULL);
		//node = ft_createnewnode(envlcontent);
        if (node == NULL) 
			return (free_env(envl), NULL);
		if (envlcontent != NULL)
			free(envlcontent);
        node->node_flag = 1;
        //add new node at the end of the envl list (libft bonus);
		i++;
    }
	return (envl);
}

t_envl *ft_envnew(void *content) 
{
	t_envl	*new_node;
    if (!content)
        return NULL;
  	new_node = malloc(sizeof(t_envl));
    if (!new_node) 
        return NULL;
    new_node->next = NULL;
	if (ft_strchr(content, '=') == 0)
    	new_node->equal_flag = 0;
	else
		new_node->equal_flag = 1;
   	new_node->identificator = identify(content, '=');
    new_node->content = envl_content_fill(content, '=');
    return (new_node);
}


t_mnshll	*mnshll_init(t_mnshll *mnshll, char **env)
{
	int	i;

	i = 0;
	if (!env || env[0][0] == '\0')
		return (NULL); //error handle????;
	mnshll = malloc(sizeof(t_mnshll));
 	if (!mnshll)
  		return (NULL);
 	mnshll->envl = env_list_init(env, i);
	if (!mnshll->envl)
		return (NULL);
 	mnshll->exit = 0;
	return (mnshll);
}


//we need to print a specific msg depending on the syntax error exmpl "Minishell : syntax error: unclosed quote marks"
				//unclosed " ' is syntax error

int main(int arc, char **arv, char **env) 
{
    t_mnshll    *mnshll;
	
	if (arc > 1)
	{
		mnshll = mnshll_init(mnshll, env);
		if (mnshll == NULL)
			return (NULL);
		while (1) 
		{
			mnshll->input = readline("Minishell <3 : ");
			if (mnshll->input == NULL)
				break;
			if (ft_strlen(mnshll->input) != 0)
				add_history(mnshll->input);
			if (lexer_syntax(mnshll, mnshll->input) == 1) //we should parse minishell whole struct, because we need to initialize stuff there 
				continue ; //bcs we dont want to quit programm if its a syntax error we want to iterate through(wait for next input)
			else //init and syntax
			{
				start_procces(mnshll);
				//free command list
			}
		}
		//free stuff;
	}
    return (0);
}

/*
int main(int arc, char **arv, char **env) 
{
    t_lexer	*lexer;
	
	lexer.input = NULL;
	arv = NULL;
	env = NULL;
	if (arc > 1)
		return (1);
    while (1) 
	{
        lexer.input = readline("Minishell <3 : ");
        if (lexer.input == NULL)
            break;
		if (ft_strlen(lexer.input) != 0)
        	add_history(lexer.input);
        lexer.tokens = initiate_lexer(lexer.input);
        if (lexer.tokens == NULL)
            continue ;
        printf("%s\n", lexer.input);
    }
	free(lexer.input);
    return (0);
}*/

