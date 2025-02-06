/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_ops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:24:34 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/02/06 18:18:21 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "pipex.h"
//#include "minishell.h"
#include "../../includes/minishell.h"
/*
	TODO: rewrite to account for multiple redirections and no pipes
	TODO: think through the usage with builtins
*/
/*
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
*/
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
/*
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
*/

/*
RULES:
TODO: figure out perimissions for output redirections
	output redirections:
		each:
			dup2 to pipe, if pipe?
			> open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			>> open(arg, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
			check not dir
			check access rights
		if more redirections
			close
			and open
		if multiple, last one wins, if no problems in other redirections 
		if exist, nothing to pipe
	input redirections:
		command uses last redir
		if second last is dir, its ok
		if heredoc - do heredoc, but use or no use depends on position
		if permssion faile SOMEWHERE, error
*/

void 	redirect_fds(t_pipex *pipex)
{
	if (pipex->current_command == 0)
	{
		ft_close(&pipex->pipe[0]);
		dup2_and_close(&pipex->pipe[1], STDOUT_FILENO);
		//if (process_rfile_name_arg(pipex) == -1)
		//	error_and_exit(pipex, DUP_FAIL);
	}
	else if (pipex->current_command == (pipex->command_count - 1))
	{
		ft_close(&pipex->pipe[1]);
		if (pipex->current_command)
		{
			if (dup2_and_close(&pipex->reserve_fd, STDIN_FILENO))
				error_and_exit(pipex, DUP_FAIL);
		}
		//if (process_wfile_name_arg(pipex) == -1)
		//	error_and_exit(pipex, DUP_FAIL);
	}
	else if (process_normal_pipe(pipex) == -1)
		error_and_exit(pipex, DUP_FAIL);
}
