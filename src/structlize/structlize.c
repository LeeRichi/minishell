/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structlize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:27:51 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/24 19:55:26 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void struct_else(t_shell *shell, t_cmd *current_cmd, int *i)
{
	if (current_cmd != NULL && current_cmd->cmd_name == NULL)
	{				
		while (shell->tokens[*i][0] == '\0' && shell->tokens[*i + 1])
			i++;
		current_cmd->cmd_name = ft_strdup(shell->tokens[*i]);
		if (!current_cmd->cmd_name)
			malloc_fail_clean_exit(shell);
	}
	else
		current_cmd->arg = ft_add_to_array(shell, current_cmd->arg, shell->tokens[*i]);
}

static void loop_tokens(t_shell *shell, t_cmd *current_cmd)
{
	int i;
    t_cmd *new_cmd;
	
	new_cmd = NULL;
	i = 0;
	while (shell->tokens[i])	
	{
        if (current_cmd == NULL || ft_strcmp(shell->tokens[i], "|") == 0)
        {
            allocate_nodes(&current_cmd, &new_cmd, shell);
            if (ft_strcmp(shell->tokens[i], "|") == 0)
                i++;
        }
        if (ft_strcmp(shell->tokens[i], "<<") == 0 || ft_strcmp(shell->tokens[i], ">>") == 0 ||
            ft_strcmp(shell->tokens[i], ">") == 0 || ft_strcmp(shell->tokens[i], "<") == 0)
			struct_redir(shell, current_cmd, &i);
		else
			struct_else(shell, current_cmd, &i);
		i++;
    }
}

//TODO: check mallocs
void ft_structlize(t_shell *shell)
{
    t_cmd *current_cmd;
	
	current_cmd = NULL;
	loop_tokens(shell, current_cmd);
	if (current_cmd)
        current_cmd->redirection_index = 0;
    if (shell->err_code == 2)
    {
        clear_cmds(shell);
        shell->exit_code = 2;
    }
}
