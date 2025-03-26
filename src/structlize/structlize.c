/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structlize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:27:51 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/26 14:36:12 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_nullize_struct(t_cmd *new_cmd)
{
	ft_bzero(new_cmd, sizeof(t_cmd));
}

void	ft_add_redirection(t_shell *shell, char ***array, char *file)
{
	*array = ft_add_to_array(shell, *array, file);
}

static void	struct_else(t_shell *shell, t_cmd *cc, int *i)
{
	if (cc != NULL && cc->cmd_name == NULL)
	{
		// while (shell->tokens[*i][0] == '\0' && shell->tokens[*i + 1])
		// 	i++;
		// if (ft_strcmp(shell->tokens[*i], ""))
		// 	printf("fuck you\n");
		cc->cmd_name = ft_strdup(shell->tokens[*i]);
		if (!cc->cmd_name)
			malloc_fail_clean_exit(shell);
	}
	else
		cc->arg = ft_add_to_array(shell, cc->arg, shell->tokens[*i]);
}

static void	loop_tokens(t_shell *shell, t_cmd *current_cmd)
{
	int		i;
	t_cmd	*new_cmd;

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
		if (ft_strcmp(shell->tokens[i], "<<") == 0
			|| ft_strcmp(shell->tokens[i], ">>") == 0
			|| ft_strcmp(shell->tokens[i], ">") == 0
			|| ft_strcmp(shell->tokens[i], "<") == 0)
			struct_redir(shell, current_cmd, &i);
		else
			struct_else(shell, current_cmd, &i);
		i++;
	}
}

//TODO: check mallocs
void	ft_structlize(t_shell *shell)
{
	t_cmd	*current_cmd;

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
