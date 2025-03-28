/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:20:26 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/28 17:42:00 by chlee2           ###   ########.fr       */
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

void	clear_cmds(t_shell *shell)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!shell || !shell->cmds)
		return ;
	current = shell->cmds;
	while (current)
	{
		next = current->next;
		ft_free_parsed_cmd(current);
		current = next;
	}
	shell->cmds = NULL;
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	malloc_fail_clean_exit(t_shell *shell)
{
	ft_printf_fd(STDERR, "malloc fail\n");
	ft_free_all(shell);
	exit(EXIT_FAILURE);
}

void	free_key_value_list(t_key_value *head)
{
	t_key_value	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}
