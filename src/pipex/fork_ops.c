/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:28:08 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/02/11 11:51:24 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "pipex.h"
//#include "minishell.h"
#include "../../includes/minishell.h"

void	in_child(t_pipex pipex)
{
	t_cmd	command;

//	ft_bzero((void *)&command, sizeof(t_command));
//	pipex.command = &command;
// TODO: handle per command redirections in redirect fds
// move 
	redirect_fds(&pipex);
	get_command(&pipex);
	command = pipex.command[pipex.current_command];
//	ft_putendl_fd("in child:", 2);
//	ft_putnbr_fd((int)pipex.current_command, 2);
//	ft_putendl_fd(command.path, 2);
	
// pipex.env? to execve
	execve(command.path, command.argv, command.env);
//	perror("after exec");
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
//TODO: consider using waitpid,	double check the intended behaviour
//TODO: check wait return -1
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
