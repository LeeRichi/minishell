/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_ops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:24:34 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/02/20 23:03:52 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "pipex.h"
//#include "minishell.h"
#include "../../includes/minishell.h"
/*
	TODO: rewrite to account for multiple redirections and no pipes
	TODO: think through the usage with builtins
*/
static void err_and_exit(char *fname, int line, t_pipex *pipex, t_perrtypes errtype)
{
	printf("%s, %d", fname, line);
	error_and_exit(pipex, errtype);
}
#define error_and_exit(x, y) err_and_exit(__FILE__, __LINE__, x, y)
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
	int	dup_res;

	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (-1);
	dup_res = dup2(fd, STDIN_FILENO);
	close(fd);
	return (dup_res);
}

int handle_outfile(char *name)
{
	int	fd;
	int	dup_res;

	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	dup_res = dup2(fd, STDOUT_FILENO);
	close(fd);
	return (dup_res);
}

int handle_append(char *name)
{
	int	fd;
	int	dup_res;

	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
	if (fd == -1)
		return (-1);
	dup_res = dup2(fd, STDOUT_FILENO);
	close(fd);
	return (dup_res);
}

int handle_heredoc_child(int *heredoc_fd)
{
	int	dup_res;

	dup_res = dup2(*heredoc_fd, STDIN_FILENO);
	close(*heredoc_fd);
	*heredoc_fd = -1;
	return (dup_res);
}
int is_last_heredoc_redir(size_t index, t_redirect_type *arr, size_t arr_size)
{
	while (++index < arr_size)
		if (arr[index] == HERE_DOC)
			return(0); 
	return (1);
}
//TODO: handle error and exit here, to give correct file name in error
//give correctt pointers to cmd forease
int process_file_redirections(t_cmd *cmd)
{
	size_t infile_count;
	size_t outfile_count;
	size_t count;

	count = 0;
	if (cmd->infiles)
		infile_count = (size_t)count_split(cmd->infiles);
	else
		infile_count = 0;
	if (cmd->outfiles)
		outfile_count = (size_t)count_split(cmd->outfiles);
	else
		outfile_count = 0;
	while (count < infile_count + outfile_count)
	{
		if (cmd->redirect_type[count] == INPUT_REDIRECT)
		{
//			ft_putstr_fd("IR", 2);
			if (handle_infile(get_redir_str(count, *cmd)) == -1)
			{
				//TODO: print error
				return (1);
			}
		}
		else if (cmd->redirect_type[count] == OUTPUT_REDIRECT)
		{
//			ft_putstr_fd("OR", 2);
			if (handle_outfile(get_redir_str(count, *cmd)) == -1)
			{
				//TODO: print error
				return (1);
			}
		}
		else if (cmd->redirect_type[count] == HERE_DOC)
		{
//			ft_putstr_fd("HD", 2);
			if (is_last_heredoc_redir(count, cmd->redirect_type, infile_count + outfile_count) &&
				handle_heredoc_child(&cmd->heredoc_fd) == -1)
			{
				//TODO: print error
				return (1);
			}
		}
		else if (cmd->redirect_type[count] == APPEND_REDIRECT)
		{
//			ft_putstr_fd("AR", 2);
			if (handle_append(get_redir_str(count, *cmd)) == -1)
			{
				//TODO: print error
				return (1);
			}
		}
		count++;
	}
	return (0);
}

void 	redirect_fds(t_pipex *pipex)
{
	if (pipex->current_command == 0)
	{
		ft_close(&pipex->pipe[0]);
		if (dup2_and_close(&pipex->pipe[1], STDOUT_FILENO) == -1)
			error_and_exit(pipex, DUP_FAIL);
	}
	else if (pipex->current_command == (pipex->command_count - 1))
	{
		ft_close(&pipex->pipe[1]);
		if (pipex->current_command)
		{
			if (dup2_and_close(&pipex->reserve_fd, STDIN_FILENO) == -1)
				error_and_exit(pipex, DUP_FAIL);
		}
	}
	else if (process_normal_pipe(pipex) == -1)
		error_and_exit(pipex, DUP_FAIL);
}
