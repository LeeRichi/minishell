/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:20:26 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/11 17:51:16 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void free_tokens(char **tokens)
{
    int i = 0;

	//temp
	if (!tokens)
		return ;
	while (tokens[i])
	{
        free(tokens[i]);
        i++;
    }
    free(tokens);

	//temp
	//*tokens = NULL;
}

void clear_tokens(t_shell *shell)
{
    if (shell->tokens)
    {
        for (int i = 0; shell->tokens[i]; i++)
        {
            free(shell->tokens[i]);
        }
        free(shell->tokens);
        shell->tokens = NULL;
    }
}

void clear_envp(t_shell *shell)
{
    if (shell->envp)
    {
        free_tokens(shell->envp);
        shell->envp = 0;
    }
}

void ft_free_all(t_shell *shell)
{
	if (shell->pipex)
	{
		free_pipex(*(shell->pipex));
		shell->pipex = 0;
	}
	clear_tokens(shell);

    //fuck
    
    if(shell->envp)
    {
        printf("envp exists\n");
        clear_envp(shell);
    }

	clear_cmds(shell);
}

void clear_cmds(t_shell *shell)
{
    t_cmd *current;
    t_cmd *next;

    if (!shell || !shell->cmds)
        return;

    current = shell->cmds;
    while (current)
    {
        next = current->next;

        // Free cmd_name
        if (current->cmd_name)
        {
            free(current->cmd_name);
            current->cmd_name = NULL;
        }

        // Free arg array
        if (current->arg)
        {
            for (int i = 0; current->arg[i]; i++)
                free(current->arg[i]);
            free(current->arg);
            current->arg = NULL;
        }

        // // Free infiles array
        if (current->infiles)
        {
            for (int i = 0; current->infiles[i]; i++)
                free(current->infiles[i]);
            free(current->infiles);
            // current->infiles = NULL;
        }

        // Free outfiles array
        if (current->outfiles)
        {
            for (int i = 0; current->outfiles[i]; i++)
                free(current->outfiles[i]);
            free(current->outfiles);
            current->outfiles = NULL;
        }

        if (current->redirect_type)
        {
            //so, enum style's free:
			free(current->redirect_type);
            current->redirect_type = NULL;
            // for (int i = 0; current->redirect_type[i]; i++)
            //     free(current->redirect_type[i]);
            // free(current->redirect_type);
            // current->redirect_type = NULL;
        }

        // Free redirection type array (if needed)
        // if (current->type)
        // {
            // free(current->type);
            // current->type = NULL;
        // }

        // Free the current command structure
        free(current);
        current = next;
    }

    // Set the cmds pointer in shell to NULL
        shell->cmds = NULL;
}

void free_matrix(char **matrix)
{
	int i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
