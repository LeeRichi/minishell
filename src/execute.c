/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 22:28:12 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/13 16:36:23 by chlee2           ###   ########.fr       */
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

// builtin error handing 
void execute(t_shell *shell)
{
	// printf("shel code: %d\n", shell->exit_code);

	int	redirection_result;
	int	exec_result;
	
	//ft_printf("%p\n", shell->cmds);
	//printf("in mainin mainin mainin mainin mainin mainin mainin mainin mainin mainin mainin main\n");
	// printf("shell cmds %p\n", shell->cmds);
	if (!shell->cmds)
	{
		// printf("fuck yoyo: %d\n", shell->exit_code);
		return ;
	}
	if (shell->cmds->next || !get_builtin_type(*(shell->cmds)))
	{
		
		exec_result = pipex_launch(shell->cmds, shell->envp, shell);
	}
	else
	{
		
		shell->cmds->shell = shell;
		redirection_result = preserve_fds(shell);
		if (redirection_result == -1)
		{
			//TODO: error cleanup and exit?
		}
		resolve_heredoc_cmds(shell->cmds, 1);
		redirection_result = process_file_redirections(shell->cmds);
		if (redirection_result == -1)
		{
			//TODO: error cleanup, no exit
		}
//TODO: pass shell as a parameter, return to exit status
		exec_result = handle_builtin(*(shell->cmds));
		if (exec_result == -1)
		{
			//TODO: error cleanup no exit
		}
		redirection_result = restore_fds(shell);
		if (redirection_result == -1)
		{
			//TODO: error cleanup and exit?
		}
	}
	shell->exit_code = exec_result;
}
