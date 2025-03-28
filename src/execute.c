/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 22:28:12 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/28 18:55:17 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	preserve_fds(t_shell *shell)
{
	if (shell->stdin_fd == -1)
		shell->stdin_fd = dup(STDIN_FILENO);
	if (shell->stdout_fd == -1)
		shell->stdout_fd = dup(STDOUT_FILENO);
	if (shell->stdin_fd == -1 || shell->stdout_fd == -1)
	{
		ft_close(&shell->stdin_fd);
		ft_close(&shell->stdout_fd);
		return (-1);
	}
	return (0);
}

static int	restore_fds(t_shell *shell)
{
	if (dup2(shell->stdin_fd, STDIN_FILENO) == -1)
		return (-1);
	if (dup2(shell->stdout_fd, STDOUT_FILENO) == -1)
		return (-1);
	return (0);
}

void	preserve_fds_and_error_exit(t_shell *shell)
{
	int	redirection_result;

	redirection_result = preserve_fds(shell);
	if (redirection_result == -1)
	{
		perror("Saving stdandard out and in fail");
		ft_free_all(shell);
		exit(1);
	}
}

void	restore_fds_and_error_exit(t_shell *shell)
{
	int	redirection_result;

	redirection_result = restore_fds(shell);
	if (redirection_result == -1)
	{
		perror("Restoring stdandard out and in fail");
		ft_free_all(shell);
		exit(1);
	}
}

void	cleanup_parent_on_redirection_fail(t_shell *shell)
{
	if (shell->cmds && shell->cmds->heredoc_fd != -1)
	{
		close(shell->cmds->heredoc_fd);
		shell->cmds->heredoc_fd = -1;
	}
	clear_cmds(shell);
	shell->exit_code = 1;
	restore_fds_and_error_exit(shell);
}
