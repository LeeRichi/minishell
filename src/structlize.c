/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structlize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:27:51 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/21 21:07:14 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int count_specific(char **tokens, char *nid)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (strcmp(tokens[i], nid) == 0)
			count++;
		i++;
	}
	return count;
}

//temp function //clean up at the end
int count_redirections(char **tokens)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (strcmp(tokens[i], "<") == 0 || strcmp(tokens[i], ">") == 0 ||
			strcmp(tokens[i], ">>") == 0 || strcmp(tokens[i], "<<") == 0)
		{
			count++;
		}
		i++;
	}
	return count;
}

//TODO: check ft_strdup
char **ft_add_to_array(char **array, const char *new_element)
{
	int i;
	int len;
	char **new_array;

	len = 0;
	if (array)
    {
        while (array[len])
            len++;
    }
    new_array = malloc(sizeof(char *) * (len + 2));
    if (!new_array)
    {
        // perror("malloc failed");
        print_error_message(error_init(MALLOC_FAIL, 0, 0));
        return NULL;
    }
	i = 0;
	while (i < len)
	{
		new_array[i] = ft_strdup(array[i]); // Duplicate each string
        //fuck ?
      	// if (!new_array[i]) {
        //     perror("strdup failed while copying array element");
		// 	free_matrix(new_array);
		// 	return NULL;
		// }
        i++;
	}
	new_array[i] = ft_strdup(new_element);
    if (!new_array[i])
    {
        // perror("strdup failed while adding to new_array");
        print_error_message(error_init(MALLOC_FAIL, 0, 0));
        free_matrix(new_array);
        return NULL;
    }
    new_array[i + 1] = NULL;
    if (array)
        free_matrix(array);
    return new_array;
}

void ft_nullize_struct(t_cmd *new_cmd)
{
	ft_bzero(new_cmd, sizeof(t_cmd));
/*
    new_cmd->cmd_name = NULL;
    new_cmd->arg = NULL;
    new_cmd->infiles = NULL;
    new_cmd->outfiles = NULL;
    memset(new_cmd->redirect_type, 0, sizeof(new_cmd->redirect_type));
    new_cmd->pipe = 0;
	new_cmd->redirection_index = 0;
	new_cmd->next = NULL;
*/
}

void ft_add_redirection(char ***array, char *file)
{
    *array = ft_add_to_array(*array, file);
    // ft_print_array(*array);
}
//TODO: free all before exit
// multiple malloc check, free possible successful allocs
void allocate_nodes(t_cmd **current_cmd, t_cmd **new_cmd, t_shell *shell)
{
    // printf("fuck\n");
    if (*current_cmd)
        (*current_cmd)->pipe = 1;
    *new_cmd = malloc(sizeof(t_cmd));
    if (!(*new_cmd))
    {
        // perror("malloc failed for new_cmd");
        print_error_message(error_init(MALLOC_FAIL, 0, 0));
        exit(EXIT_FAILURE);
    }
    ft_nullize_struct(*new_cmd);
	(*new_cmd)->redirect_type = malloc(sizeof(t_redirect_type) * count_redirections(shell->tokens));
	(*new_cmd)->outfiles = malloc(sizeof(char *) * (count_specific(shell->tokens, ">") + 1));
	(*new_cmd)->infiles = malloc(sizeof(char *) * (count_specific(shell->tokens, "<") + 1));
    if (!(*new_cmd)->redirect_type || !(*new_cmd)->outfiles || !(*new_cmd)->infiles)
	// if (!(*new_cmd)->redirect_type || !(*new_cmd)->outfiles)
    {
        // perror("malloc failed for redirect_type || intfiles || outfiles");
        print_error_message(error_init(MALLOC_FAIL, 0, 0));
        exit(EXIT_FAILURE);
    }
    memset((*new_cmd)->redirect_type, 0, sizeof(t_redirect_type) * count_redirections(shell->tokens));
    memset((*new_cmd)->outfiles, 0, sizeof(char *) * (count_specific(shell->tokens, ">") + 1));
    memset((*new_cmd)->infiles, 0, sizeof(char *) * (count_specific(shell->tokens, "<") + 1));

    if (*current_cmd)
        (*current_cmd)->next = *new_cmd;
    else
    {
        shell->cmds = *new_cmd;
        // printf("shell->cmds...: %s\n", shell->cmds->cmd_name);
    }
    *current_cmd = *new_cmd;
}
//TODO: check that the infiles outfiles are not 0 after add redirection
void handle_redirection(t_cmd *current_cmd, char *operator, char *file)
{
	int i;

	i = current_cmd->redirection_index;
    if (strcmp(operator, "<") == 0)
    {
        ft_add_redirection(&current_cmd->infiles, file); //might need to allocate this too
        current_cmd->redirect_type[i] = INPUT_REDIRECT;
	}
	else if (strcmp(operator, ">") == 0 || strcmp(operator, ">>") == 0)
    {
		ft_add_redirection(&current_cmd->outfiles, file);
        if (strcmp(operator, ">") == 0)
        {
			current_cmd->redirect_type[i] = OUTPUT_REDIRECT;
        }
        else
            current_cmd->redirect_type[i] = APPEND_REDIRECT;
    }
    else if (strcmp(operator, "<<") == 0)
    {
        ft_add_redirection(&current_cmd->infiles, file);
        current_cmd->redirect_type[i] = HERE_DOC;
    }
	current_cmd->redirection_index = i + 1;
}

//TODO: check mallocs
void ft_structlize(t_shell *shell)
{
    int i = 0;
    t_cmd *current_cmd = NULL;
    t_cmd *new_cmd = NULL;

	// printf("has quote??? %d\n", shell->has_quotes);

	while (shell->tokens[i])	
	{
        if (current_cmd == NULL || strcmp(shell->tokens[i], "|") == 0)
        {
            allocate_nodes(&current_cmd, &new_cmd, shell);
            // if (current_cmd == NULL) {
            //     ft_printf_fd(STDERR, "Memory allocation failed for new command\n");
            //     return;
            // }
            if (strcmp(shell->tokens[i], "|") == 0)
                i++;
        }
        if (strcmp(shell->tokens[i], "<<") == 0 || strcmp(shell->tokens[i], ">>") == 0 ||
            strcmp(shell->tokens[i], ">") == 0 || strcmp(shell->tokens[i], "<") == 0)
        {
            // dump
            if (shell->has_quotes)
            {
                // printf("fuckkkkk\n");
                current_cmd->arg = ft_add_to_array(current_cmd->arg, shell->tokens[i]);
            }
            // if (shell->tokens[i + 1] && ft_start_with_specials(shell->tokens[i + 1]))
            else if (shell->tokens[i + 1] != NULL && ft_start_with_specials(shell->tokens[i + 1]))
            {
                // printf("has_quote: %d\n", shell->has_quotes);
                ft_printf_fd(STDERR, "minishell: syntax error\n");
                shell->err_code = 2;
                shell->exit_code = 2;
                // return ;
            }
            // if (shell->tokens[i + 1][0] == '\0')
            else if (shell->tokens[i + 1] != NULL && shell->tokens[i + 1][0] == '\0')
            {
                // printf("found consecutive redir, plz put a flag to this node, which tell the executor - dont exe it.\n");
                current_cmd->ambiguous_flag_node = 1;
            }
			else if (shell->tokens[i + 1] != NULL)
			{
				handle_redirection(current_cmd, shell->tokens[i], shell->tokens[i + 1]);
				i++;
			}
            else if (shell->tokens[i + 1] == NULL) //quotes as last token
            {
				// ft_printf_fd(STDERR, "minishell: syntax error\n");
				// shell->err_code = 2;
				// shell->exit_code = 2;
                if (shell->has_quotes)
                {
					current_cmd->arg = ft_add_to_array(current_cmd->arg, shell->tokens[i]);
                }
				else
				{
					ft_printf_fd(STDERR, "minishell: syntax error\n");
					shell->err_code = 2;
					shell->exit_code = 2;
				}
                // fprintf(stderr, "Syntax error: missing file after '%s'\n", shell->tokens[i]);
                // return; // Avoid accessing out-of-bounds memory
            }
            else if (current_cmd != NULL)
            {
				//can i write malloc for infiles and outfiles here?
                if (shell->has_quotes) //fuck
                {
				    current_cmd->cmd_name = strdup(shell->tokens[i]);
                    if (current_cmd->cmd_name == NULL) {
                        ft_printf_fd(STDERR, "Memory allocation failed for command name\n");
                        return;
                    }
                    shell->has_quotes = 0;
                }
                else
			        handle_redirection(current_cmd, shell->tokens[i], shell->tokens[i + 1]);
            }
            else
                ft_printf_fd(STDERR, "Error: Redirection without a command\n");
			// i++;
		}
		// else
		// {
		// 	printf("fuckkkkk\n");
		// 	if (current_cmd != NULL && current_cmd->cmd_name == NULL)
		// 	{
		// 		while (i < shell->token_count && shell->tokens[i][0] == '\0' && shell->tokens[i + 1]) // skip empty tokens
		// 			i++;
		// 		if (i < shell->token_count && shell->tokens[i] != NULL && )
		// 			current_cmd->cmd_name = strdup(shell->tokens[i]);
		// 	}
		// 	else
		// 	{
		// 		if (i < shell->token_count && shell->tokens[i] != NULL)
		// 			current_cmd->arg = ft_add_to_array(current_cmd->arg, shell->tokens[i]);
		// 	}
		// 	// i++;
		// }

		//old
		else
		{
			if (current_cmd != NULL && current_cmd->cmd_name == NULL)
            {				
                while (shell->tokens[i][0] == '\0' && shell->tokens[i + 1]) //skip empty tokens
                    i++;
				current_cmd->cmd_name = strdup(shell->tokens[i]);

                //new
                // if (current_cmd->cmd_name == NULL) {
                //     ft_printf_fd(STDERR, "Memory allocation failed for command name\n");
                //     return; // Ensure you return here to avoid further memory accesses.
                // }
            }
			else
				current_cmd->arg = ft_add_to_array(current_cmd->arg, shell->tokens[i]);
		}
		i++;
    }
	if (current_cmd)
        current_cmd->redirection_index = 0;

    //fuck temp

    // printf("err_code: %d\n", shell->err_code);
    if (shell->err_code == 2)
    {
        // printf("checker !!!!!!!!!!!!!11\n");
        clear_cmds(shell);
        shell->exit_code = 2;
    }
}
