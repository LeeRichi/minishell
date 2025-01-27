/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:28:08 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/12/10 13:18:11 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	in_child(t_pipex pipex)
{
	t_command	command;

	ft_bzero((void *)&command, sizeof(t_command));
	pipex.command = &command;
	redirect_fds(&pipex);
	get_command(pipex.first_command, &pipex);
	execve(command.path, command.argv, command.env);
	if (errno == ENOENT)
		error_and_exit(&pipex, CMD_FILE_NOT_FOUND);
	error_and_exit(&pipex, EXECVE_FAIL);
}

int	after_fork(pid_t fork_result, t_pipex *pipex)
{
	if (fork_result == -1)
	{
		wait_all(*pipex);
		error_and_exit(pipex, FORK_FAIL);
	}
	if (fork_result == 0)
		in_child(*pipex);
	else if (pipex->current_command != pipex->command_count - 1)
		ft_close(&(pipex->pipe[1]));
	return (0);
}

int	wait_all(t_pipex pipex)
{
	int	wstatus;
	int	exit_status;

	wstatus = 0;
	exit_status = EXIT_FAILURE;
	while (pipex.current_command--)
	{
		if (wait(&wstatus) == pipex.last_pid)
		{
			if (WIFEXITED(wstatus))
				exit_status = WEXITSTATUS(wstatus);
			else if (WIFSIGNALED(wstatus))
				exit_status = 128 + WTERMSIG(wstatus);
		}
	}
	return (exit_status);
}
