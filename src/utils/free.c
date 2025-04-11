/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:20:26 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/11 16:25:30 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
	{
		return ;
	}
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	clear_tokens(t_shell *shell)
{
	if (shell->tokens)
	{
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
	//new
	if (shell->expanded_tokens_arr)
	{
		free(shell->expanded_tokens_arr);
	//	free_tokens(shell->expanded_tokens_arr);
		shell->expanded_tokens_arr = NULL;
	}
}

void	clear_envp(t_shell *shell)
{
	if (shell->envp)
	{
		free_tokens(shell->envp);
		shell->envp = 0;
	}
}

void	ft_free_all(t_shell *shell)
{
	if (!shell)
		return ;
	clear_history();
	if (shell->pipex)
	{
		free_pipex(*(shell->pipex));
		shell->pipex = 0;
	}
	clear_tokens(shell);
	if (shell->stdin_fd != -1)
		close(shell->stdin_fd);
	if (shell->stdout_fd != -1)
		close(shell->stdout_fd);
	if (shell->envp)
	{
		clear_envp(shell);
	}
	clear_cmds(shell);
}

void	ft_free_parsed_cmd(t_cmd *current)
{
	if (current->cmd_name)
		free(current->cmd_name);
	free_tokens(current->arg);
	free_tokens(current->infiles);
	free_tokens(current->outfiles);
	if (current->redirect_type)
		free(current->redirect_type);
	current->cmd_name = NULL;
	current->arg = NULL;
	current->infiles = NULL;
	current->outfiles = NULL;
	current->redirect_type = NULL;
	free(current);
}
