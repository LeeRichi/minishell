/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 23:22:51 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/04/03 18:46:59 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	t_cmd_list_count(t_cmd *head)
{
	int	counter;

	counter = 0;
	while (head)
	{
		counter++;
		head = head->next;
	}
	return (counter);
}

int	pipex_loop(t_pipex *pipex)
{
	int		wait_all_return;
	pid_t	pid;

	before_child_process_signal();
	while (pipex->current_command < pipex->command_count)
	{
		before_fork(pipex);
		pid = fork();
		if (pid != -1)
			pipex->last_pid = pid;
		after_fork(pid, pipex);
		pipex->current_command++;
	}
	ft_close(&pipex->pipe[0]);
	ft_close(&pipex->pipe[1]);
	wait_all_return = wait_all(*pipex);
	set_minishell_signal();
	return (wait_all_return);
}

int	resolve_heredoc_cmds_or_error_and_exit(t_pipex *pipex,
	int command_count, t_shell *shell)
{
	if (!resolve_heredoc_cmds(pipex->command, command_count))
	{
		if (shell->err_code)
		{
			if (shell->pipex)
				free_pipex(*(shell->pipex));
			shell->pipex = 0;
			return (shell->exit_code);
		}
		else
		{
			error_and_exit(pipex, error_init(HEREDOC_FAIL, 0, 0));
		}
	}
	return (shell->exit_code);
}

int	pipex_launch(t_cmd *cmds, char **env, t_shell *shell)
{
	t_pipex	pipex;
	int		wait_all_return;
	int		command_count;

	command_count = t_cmd_list_count(cmds);
	shell->pipex = 0;
	pipex = get_pipex(command_count, cmds, env, shell);
	if (!pipex.command)
	{
		perror("pipex alloc fail");
		return (0);
	}
	shell->pipex = &pipex;
	resolve_heredoc_cmds_or_error_and_exit(&pipex, command_count, shell);
	if (shell->err_code)
	{
		shell->err_code = 0;
		return (shell->exit_code);
	}
	wait_all_return = pipex_loop(&pipex);
	free_pipex(pipex);
	shell->pipex = 0;
	return (wait_all_return);
}
