/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_ops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:24:34 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/25 21:13:19 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_normal_pipe(t_pipex *pipex)
{
	ft_close(&pipex->pipe[0]);
	if (dup2_and_close(&pipex->reserve_fd, STDIN_FILENO) == -1)
		error_and_exit(pipex, error_init(DUP_FAIL, 0, 0));
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
			error_and_exit(pipex, error_init(PIPE_FAIL, 0, 0));
	}
}

char	*get_redir_str(int index, t_cmd cmd)
{
	t_redirect_type	*type;
	char			**infiles;
	char			**outfiles;
	int				count;

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

int	handle_infile(char *name)
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

int	handle_outfile(char *name)
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

int	handle_append(char *name)
{
	int	fd;
	int	dup_res;

	fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (-1);
	dup_res = dup2(fd, STDOUT_FILENO);
	close(fd);
	return (dup_res);
}

int	handle_heredoc_child(int *heredoc_fd)
{
	int	dup_res;

	dup_res = dup2(*heredoc_fd, STDIN_FILENO);
	close(*heredoc_fd);
	*heredoc_fd = -1;
	return (dup_res);
}

int	is_last_heredoc_redir(size_t index, t_redirect_type *arr, size_t arr_size)
{
	while (++index < arr_size)
		if (arr[index] == HERE_DOC)
			return (0);
	return (1);
}

size_t	handle_infile_and_print_error(size_t count, t_cmd *cmd)
{
	if (handle_infile(get_redir_str(count, *cmd)) == -1)
	{
		print_error_message(error_init(FILE_REDIR_FAIL,
				get_redir_str(count, *cmd), 0));
		return (1);
	}
	return (0);
}

size_t	handle_outfile_and_print_error(size_t count, t_cmd *cmd)
{
	if (handle_outfile(get_redir_str(count, *cmd)) == -1)
	{
		print_error_message(error_init(FILE_REDIR_FAIL,
				get_redir_str(count, *cmd), 0));
		return (1);
	}
	return (0);
}

size_t	handle_append_and_print_error(size_t count, t_cmd *cmd)
{
	if (handle_append(get_redir_str(count, *cmd)) == -1)
	{
		print_error_message(error_init(FILE_REDIR_FAIL,
				get_redir_str(count, *cmd), 0));
		return (1);
	}
	return (0);
}

size_t	handle_heredoc_and_print_error(size_t count,
	t_cmd *cmd, size_t file_count)
{
	if (is_last_heredoc_redir(count, cmd->redirect_type, file_count)
		&& handle_heredoc_child(&cmd->heredoc_fd) == -1)
	{
		print_error_message(error_init(FILE_REDIR_FAIL,
				get_redir_str(count, *cmd), 0));
		return (1);
	}
	return (0);
}

size_t	count_files(t_cmd *cmd)
{
	size_t	infile_count;
	size_t	outfile_count;

	if (cmd->infiles)
		infile_count = (size_t)count_split(cmd->infiles);
	else
		infile_count = 0;
	if (cmd->outfiles)
		outfile_count = (size_t)count_split(cmd->outfiles);
	else
		outfile_count = 0;
	return (infile_count + outfile_count);
}

int	handle_redirection_check_error(size_t count, t_cmd *cmd, size_t file_count)
{
	if (cmd->redirect_type[count] == INPUT_REDIRECT)
	{
		if (handle_infile_and_print_error(count, cmd))
			return (1);
	}
	else if (cmd->redirect_type[count] == OUTPUT_REDIRECT)
	{
		if (handle_outfile_and_print_error(count, cmd))
			return (1);
	}
	else if (cmd->redirect_type[count] == HERE_DOC)
	{
		if (handle_heredoc_and_print_error(count, cmd, file_count))
			return (1);
	}
	else if (cmd->redirect_type[count] == APPEND_REDIRECT)
	{
		if (handle_append_and_print_error(count, cmd))
			return (1);
	}
	return (0);
}

int	process_file_redirections(t_cmd *cmd)
{
	size_t	file_count;
	size_t	count;

	count = 0;
	if (cmd->ambiguous_flag_node)
	{
		print_error_message(error_init(AMBIGOUS_REDIR, 0, 0));
		return (1);
	}
	file_count = count_files(cmd);
	while (count < file_count)
	{
		if (handle_redirection_check_error(count, cmd, file_count))
			return (1);
		count++;
	}
	return (0);
}

void	redirect_fds(t_pipex *pipex)
{
	if (pipex->current_command == 0)
	{
		ft_close(&pipex->pipe[0]);
		if (dup2_and_close(&pipex->pipe[1], STDOUT_FILENO) == -1)
			error_and_exit(pipex, error_init(DUP_FAIL, 0, 0));
	}
	else if (pipex->current_command == (pipex->command_count - 1))
	{
		ft_close(&pipex->pipe[1]);
		if (pipex->current_command)
		{
			if (dup2_and_close(&pipex->reserve_fd, STDIN_FILENO) == -1)
				error_and_exit(pipex, error_init(DUP_FAIL, 0, 0));
		}
	}
	else if (process_normal_pipe(pipex) == -1)
		error_and_exit(pipex, error_init(DUP_FAIL, 0, 0));
}
