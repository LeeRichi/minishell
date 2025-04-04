/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:54:59 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/04/03 17:47:26 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_cmd_parent(t_shell *shell)
{
	shell->cmds->shell = shell;
	preserve_fds_and_error_exit(shell);
	if (!resolve_heredoc_cmds(shell->cmds, 1))
	{
		if (shell->err_code)
		{
			shell->err_code = 0;
			restore_fds_and_error_exit(shell);
			return ;
		}
		else
		{
			print_error_message(error_init(HEREDOC_FAIL, 0, 0));
			ft_free_all(shell);
			exit(1);
		}
	}
	if (process_file_redirections(shell->cmds))
	{
		cleanup_parent_on_redirection_fail(shell);
		return ;
	}
	shell->exit_code = handle_builtin(*(shell->cmds));
	restore_fds_and_error_exit(shell);
}

void	execute(t_shell *shell)
{
	if (!shell->cmds)
	{
		return ;
	}
	if (shell->cmds->next || !get_builtin_type(*(shell->cmds)))
		shell->exit_code = pipex_launch(shell->cmds, shell->envp, shell);
	else
		execute_cmd_parent(shell);
}
