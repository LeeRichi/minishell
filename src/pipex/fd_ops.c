/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_ops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:24:34 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/02/12 22:17:53 by mbutuzov         ###   ########.fr       */
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
		no need to special rulre for folder
		if heredoc - do heredoc, but use or no use depends on position
		fd = open(pipex->infile, O_RDONLY);
		if permssion faile SOMEWHERE, error
*/
/*

base the logic on the ordered types

add_input redir
direction: infile | oufile

*/
/*
t_redirect_type get_redirect_type(int direction, int index, t_redirect_type *ordered_types)
{
	int irrelevant_count;

	irrelevant_count = 0;
	if (direction == 0)
	{
		if (ordered_types[index] == )
	}
	else
	
}

//WIP
int attempt_redirect(t_redirection redir)
{
	int fd[2];
	int fork_return;
//TODO: dup2 checks
	if (redir.type == INPUT_REDIRECT)
	{
		fd[0] = open(pipex->infile, O_RDONLY);
		if (fd[0] == -1)
		{
//error and exit
		}
		dup2(fd[0], 0);
		close(fd[0]);
		
	} else if (redir.type == OUTPUT_REDIRECT)
	{
		fd[0] = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd[0] == -1)
		{
//error and exit
		}
		dup2(fd[0], 1);
		close(fd[0]);
		
	} else if (redir.type == APPEND_REDIRECT)
	{
		fd[0] = open(arg, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
		if (fd[0] == -1)
		{
//error and exit
		}
		dup2(fd[0], 1);
		close(fd[0]);
		
	} else if (redir.type == HERE_DOC)
	{
		if (pipe(fd) == -1)
		{
// TODO: error and exit?
		}
		fork_return = fork();
		if (fork_return == 0)
		{
// heredoc
		}
		else
		{
// parent
		}
	}
}

void handle_file_redirections(t_pipex *pipex)
{
	size_t infile_count;
	size_t outfile_count;
	char **infiles;
	char **outfiles;
	size_t i;

	i = 0;
	infiles = pipex->command[pipex->current_command].infiles;
	outfiles = pipex->command[pipex->current_command].outfiles;
	infile_count = (size_t)count_split(infiles);
	outfile_count = (size_t)count_split(outfiles);
	pipex->command[pipex->current_command].type;
	while (i < infile_count + outfile_count)
	{
		pipex->type[i]
		i++;
	}
}
*/

//char *get_redir_str(int index, char **infiles, char **outfiles, t_redirect_type *type)
char *get_redir_str(int index, t_cmd cmd)
{
	int			fd;
	int			count;
	t_redirect_type	*type;
	char		**infiles;
	char		**outfiles;

	fd = -1;
	count = 0;
	type = cmd.redirect_type;
	infiles = cmd.infiles;
	outfiles = cmd.outfiles;
	while (count < index)
	{
		if (type[count] == INPUT_REDIRECT || type[count] == HERE_DOC)
			infiles++;
		else
			outfiles++;
		count++;
	}
	if (type[count] == INPUT_REDIRECT || type[count] == HERE_DOC)
		return (*infiles);
	return (*outfiles);
}

//TODO: think cleanup strategy, consider adding shell and pipex pointers to cmd, just because its easy

int handle_infile(char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (dup2(fd, STDIN_FILENO));
}

int handle_outfile(char *name)
{
	int	fd;

	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	return (dup2(fd, STDOUT_FILENO));
}

int handle_append(char *name)
{
	int	fd;

	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
	if (fd == -1)
		return (-1);
	return (dup2(fd, STDOUT_FILENO));
}

int handle_heredoc_child(int heredoc_fd)
{
	return (dup2(heredoc_fd, STDIN_FILENO));
}

//TODO: handle error and exit here, to give correct file name in error
//give correctt pointers to cmd forease
void process_file_redirections(t_cmd cmd, t_pipex pipex)
{
	size_t infile_count;
	size_t outfile_count;
	size_t count;

	count = 0;
	if (cmd.infiles)
		infile_count = (size_t)count_split(cmd.infiles);
	else
		infile_count = 0;
	if (cmd.outfiles)
		outfile_count = (size_t)count_split(cmd.outfiles);
	else
		outfile_count = 0;
	while (count < infile_count + outfile_count)
	{
		if (cmd.redirect_type[count] == INPUT_REDIRECT)
		{
			ft_putstr_fd("IR", 2);
			if (handle_infile(get_redir_str(count, cmd)) == -1)
				//TODO: ERROR and EXIT
				error_and_exit(&pipex, RFILE_FAIL);
		}
		else if (cmd.redirect_type[count] == OUTPUT_REDIRECT)
		{
			ft_putstr_fd("OR", 2);
			if (handle_outfile(get_redir_str(count, cmd)) == -1)
				//TODO: ERROR and EXIT
				error_and_exit(&pipex, WFILE_FAIL);
		}
		else if (cmd.redirect_type[count] == HERE_DOC)
		{
			ft_putstr_fd("HD", 2);
			if (handle_heredoc_child(cmd.heredoc_fd) == -1)
				//TODO: ERROR and EXIT
				error_and_exit(&pipex, HEREDOC_FAIL);
		}
		else if (cmd.redirect_type[count] == APPEND_REDIRECT)
		{
			ft_putstr_fd("AR", 2);
			if (handle_append(get_redir_str(count, cmd)) == -1)
				//TODO: ERROR and EXIT
				error_and_exit(&pipex, APPEND_FAIL);
		}
		count++;
	}
}

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
	process_file_redirections(pipex->command[pipex->current_command], *pipex);
}
