/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structlize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:27:51 by chlee2            #+#    #+#             */
/*   Updated: 2025/02/05 16:22:42 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
        perror("malloc failed");
        return NULL;
    }
	i = 0;
	while (i < len)
	{
		new_array[i] = ft_strdup(array[i]); // Duplicate each string
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
        perror("strdup failed while adding to new_array");
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
    new_cmd->cmd_name = NULL;
    new_cmd->arg = NULL;
    new_cmd->infiles = NULL;
    new_cmd->outfiles = NULL;
    memset(new_cmd->redirect_type, 0, sizeof(new_cmd->redirect_type)); 
    new_cmd->pipe = 0;
	new_cmd->redirection_index = 0;
	new_cmd->next = NULL;
}

//temp
// void ft_print_array(char **array)
// {
//     if (!array)
//     {
//         printf("Array is NULL\n");
//         return;
//     }

//     printf("Array contents:\n");
//     for (int i = 0; array[i] != NULL; i++)  // Iterate through strings
//     {
//         printf("[%d]: %s\n", i, array[i]);
//     }
// }

void ft_add_redirection(char ***array, char *file)
{
    *array = ft_add_to_array(*array, file);
    // ft_print_array(*array);
}

void handle_pipe(t_cmd **current_cmd, t_cmd **new_cmd, t_shell *shell)
{
    if (*current_cmd)
        (*current_cmd)->pipe = 1;
    *new_cmd = malloc(sizeof(t_cmd));
    if (!(*new_cmd))
    {
        perror("malloc failed for new_cmd");
        exit(EXIT_FAILURE);
    }
    ft_nullize_struct(*new_cmd);
    if (*current_cmd)
        (*current_cmd)->next = *new_cmd;
    else
        shell->cmds = *new_cmd;
    *current_cmd = *new_cmd;
}

void handle_redirection(t_cmd *current_cmd, char *operator, char *file)
{
	int i;

	i = current_cmd->redirection_index;
	
    if (strcmp(operator, "<") == 0)
    {
        ft_add_redirection(&current_cmd->infiles, file);
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


void ft_structlize(t_shell *shell)
{
    int i = 0;
    t_cmd *current_cmd = NULL;
    t_cmd *new_cmd = NULL;

	while (shell->tokens[i])
	{
        if (current_cmd == NULL || strcmp(shell->tokens[i], "|") == 0)
        {
            handle_pipe(&current_cmd, &new_cmd, shell);
            if (strcmp(shell->tokens[i], "|") == 0)
                i++;
        }
        if (strcmp(shell->tokens[i], "<<") == 0 || strcmp(shell->tokens[i], ">>") == 0 ||
            strcmp(shell->tokens[i], ">") == 0 || strcmp(shell->tokens[i], "<") == 0)
        {
            if (shell->tokens[i + 1] == NULL)
            {
                fprintf(stderr, "Syntax error: missing file after '%s'\n", shell->tokens[i]);
                return; // Avoid accessing out-of-bounds memory
            }
            if (current_cmd != NULL)
            {
			    handle_redirection(current_cmd, shell->tokens[i], shell->tokens[i + 1]);
            }
            else
                fprintf(stderr, "Error: Redirection without a command\n");
			i++;
		}
		else
        {
            if (current_cmd->cmd_name == NULL)
                current_cmd->cmd_name = strdup(shell->tokens[i]);
            else
                current_cmd->arg = ft_add_to_array(current_cmd->arg, shell->tokens[i]);
		}
		i++;
    }
	if (current_cmd)
        current_cmd->redirection_index = 0;
}
