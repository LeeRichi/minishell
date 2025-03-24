/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 22:28:12 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/23 17:25:58 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	params: shell
	if shell has no args - do nothing
	if shell has 1 builtin arg - preserve fds, redir, execute builtin, return fds
	otherwise execute in pipex
	execute builtin vs execute external
	make is builtin function
	if builtin, exec as builtin, always clean up resources
	call it in child or in parent
*/

// TODO: add clenup for preserved fds to shell struct
static int preserve_fds(t_shell *shell)
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

// TODO: sufficient returns?
static int restore_fds(t_shell *shell)
{
	if (dup2(shell->stdin_fd, STDIN_FILENO) == -1)
		return (-1);
	if (dup2(shell->stdout_fd, STDOUT_FILENO) == -1)
		return (-1);
	return (0);
}

void preserve_fds_and_error_exit(t_shell *shell)
{
	int	redirection_result;

	redirection_result = preserve_fds(shell);
	if (redirection_result == -1)
	{
		//TODO: error cleanup and exit?
		perror("Saving stdandard out and in fail");
		ft_free_all(shell);
		exit(1);
	}
}

void restore_fds_and_error_exit(t_shell *shell)
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

// builtin error handing 
void execute(t_shell *shell)
{
	// printf("shel code: %d\n", shell->exit_code);

	int	redirection_result;
	int	exec_result;
	
	if (!shell->cmds)
	{
		return ;
	}
	if (shell->cmds->next || !get_builtin_type(*(shell->cmds)))
	{
		exec_result = pipex_launch(shell->cmds, shell->envp, shell);
	}
	else
	{
		shell->cmds->shell = shell;
		preserve_fds_and_error_exit(shell);
		if (!resolve_heredoc_cmds(shell->cmds, 1))
		{
			if (shell->err_code)
			{
			/*
				TODO: add to separate function
			*/
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
		redirection_result = process_file_redirections(shell->cmds);
		if (redirection_result)
		{
			//TODO: error cleanup, no exit
//			
			if (shell->cmds && shell->cmds->heredoc_fd != -1)
			{
				close(shell->cmds->heredoc_fd);
				shell->cmds->heredoc_fd = -1;
			}
			clear_cmds(shell);
			shell->exit_code = 1;
			restore_fds_and_error_exit(shell);
			return ;
		}
//TODO: pass shell as a parameter, return to exit status
		exec_result = handle_builtin(*(shell->cmds));
		shell->exit_code = exec_result;
		restore_fds_and_error_exit(shell);
	}
	shell->exit_code = exec_result;
}
