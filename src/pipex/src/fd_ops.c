/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_ops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:24:34 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/12/09 15:04:11 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	process_rfile_name_arg(t_pipex *pipex)
{
	int	fd;

	ft_close(&pipex->pipe[0]);
	fd = open(pipex->infile, O_RDONLY);
	if (fd == -1)
		error_and_exit(pipex, RFILE_FAIL);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		error_and_exit(pipex, DUP_FAIL);
	}
	close(fd);
	return (dup2_and_close(&pipex->pipe[1], STDOUT_FILENO));
}

int	process_wfile_name_arg(t_pipex *pipex)
{
	char	*arg;
	int		fd;

	arg = pipex->outfile;
	ft_close(&pipex->pipe[1]);
	if (pipex->current_command)
	{
		if (dup2_and_close(&pipex->reserve_fd, STDIN_FILENO))
			error_and_exit(pipex, DUP_FAIL);
	}
	fd = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_and_exit(pipex, WFILE_FAIL);
	return (dup2_and_close(&fd, STDOUT_FILENO));
}

int	process_normal_pipe(t_pipex *pipex)
{
	ft_close(&pipex->pipe[0]);
	if (dup2_and_close(&pipex->reserve_fd, STDIN_FILENO) == -1)
		error_and_exit(pipex, DUP_FAIL);
	return (dup2_and_close(&pipex->pipe[1], STDOUT_FILENO));
}

void	before_fork(t_pipex *pipex)
{
	if (pipex->current_command)
	{
		ft_close(&(pipex->reserve_fd));
		pipex->reserve_fd = pipex->pipe[0];
	}
	if (pipex->current_command < pipex->command_count - 1)
	{
		if (pipe(pipex->pipe) == -1)
			error_and_exit(pipex, PIPE_FAIL);
	}
}

void	redirect_fds(t_pipex *pipex)
{
	if (pipex->current_command == 0)
	{
		if (process_rfile_name_arg(pipex) == -1)
			error_and_exit(pipex, DUP_FAIL);
	}
	else if (pipex->current_command == (pipex->command_count - 1))
	{
		if (process_wfile_name_arg(pipex) == -1)
			error_and_exit(pipex, DUP_FAIL);
	}
	else if (process_normal_pipe(pipex) == -1)
		error_and_exit(pipex, DUP_FAIL);
}
