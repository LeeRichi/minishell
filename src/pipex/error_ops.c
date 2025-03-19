/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:21:50 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/19 16:05:15 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	resolve_exit_code(t_perrtypes errtype)
{
	if (errtype == CMD_NOT_FOUND || errtype == CMD_FILE_NOT_FOUND)
		exit(127);
	if (errtype == EXECVE_FAIL || errtype == PROG_FILE_IS_DIR)
		exit(126);
	exit(EXIT_FAILURE);
}
/*

static void	write_smth_with_colon_fd(char *smth, int fd)
{
	ft_putstr_fd(smth, fd);
	ft_putstr_fd(": ", fd);
}
*/
/*
static void	print_error_message(t_pipex pipex, t_perrtypes errtype)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	if (errtype == RFILE_FAIL)
		write_smth_with_colon_fd(pipex.infile, STDERR_FILENO);
	else if (errtype == WFILE_FAIL)
		write_smth_with_colon_fd(pipex.outfile, STDERR_FILENO);
	else if (pipex.command)
	{
		if (errtype == EXECVE_FAIL && pipex.command->path)
			write_smth_with_colon_fd(pipex.command->path, STDERR_FILENO);
		else if (pipex.command->argv && pipex.command->argv[0])
			write_smth_with_colon_fd(pipex.command->argv[0], STDERR_FILENO);
		else if (pipex.command->input_arg)
			write_smth_with_colon_fd(pipex.command->input_arg, STDERR_FILENO);
	}
	if (errtype == CMD_NOT_FOUND)
		ft_putendl_fd("Command not found", STDERR_FILENO);
	else if (errtype == PROG_FILE_IS_DIR)
		ft_putendl_fd(strerror(EISDIR), STDERR_FILENO);
	else
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}
*/

/*
	error types:

	MALLOC_FAIL,
	CMD_NOT_FOUND,
	CMD_FILE_NOT_FOUND,
	PROG_FILE_IS_DIR,
	FILE_NOT_FOUND,
	DUP_FAIL,
	HEREDOC_FAIL,
	RFILE_FAIL,
	WFILE_FAIL,
	APPEND_FAIL,
	OPEN_FAIL,
	PERMISSION_FAIL,
	EXECVE_FAIL,
	PIPE_FAIL,
	FORK_FAIL
		
*/

/*
static void	print_error_message(t_error error)
{
	if (error.errtype == CMD_NOT_FOUND)
		ft_putstr_fd("pipex: ", STDERR_FILENO);
	if (errtype == RFILE_FAIL)
		write_smth_with_colon_fd(pipex.infile, STDERR_FILENO);
	else if (errtype == WFILE_FAIL)
		write_smth_with_colon_fd(pipex.outfile, STDERR_FILENO);
	else if (pipex.command)
	{
		if (errtype == EXECVE_FAIL && pipex.command->path)
			write_smth_with_colon_fd(pipex.command->path, STDERR_FILENO);
		else if (pipex.command->argv && pipex.command->argv[0])
			write_smth_with_colon_fd(pipex.command->argv[0], STDERR_FILENO);
		else if (pipex.command->input_arg)
			write_smth_with_colon_fd(pipex.command->input_arg, STDERR_FILENO);
	}
	if (errtype == CMD_NOT_FOUND)
		ft_putendl_fd("Command not found", STDERR_FILENO);
	else if (errtype == PROG_FILE_IS_DIR)
		ft_putendl_fd(strerror(EISDIR), STDERR_FILENO);
	else
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
}
*/

t_error error_init(t_perrtypes errtype, char *file_name, char *command_name)
{
	t_error error;

//	ft_bzero(&error, sizeof(t_error));
	error.errtype = errtype;
	error.file_name = file_name;
	error.command_name = command_name;
	return (error);
}

/*static void	print_error_message(char *str1, char *str2, char *str3, char *str4)
{
	char *arr[4];

	arr[0] = str1;
	arr[1] = str2;
	arr[2] = str3;
	arr[3] = str4;
	
}
*/
char	*get_error_message(char *str1, char *str2, char *str3)
{
	char *arr[4];
	char *sep = ": ";

	arr[0] = str1;
	arr[1] = str2;
	arr[2] = str3;
//	arr[3] = str4;
	
	return ft_split_join(arr, sep);
	
}

//wip 
void	print_error_message(t_error error)
{
	char *error_message;

	error_message = 0;
	if (error.errtype == CMD_NOT_FOUND)
	{
		error_message = get_error_message(error.command_name, "command not found", 0);
	}
	else if (error.errtype == PERMISSION_FAIL)
	{
		error_message = get_error_message(SHELL_NAME, error.file_name, strerror(EACCES));
	}
	else if (error.errtype == FILE_NOT_FOUND)
	{
		error_message = get_error_message(SHELL_NAME, error.file_name, strerror(ENOENT));
	}
	else if(error.errtype == MALLOC_FAIL)
	{
		perror("Malloc fail");
	}
	else if (error.errtype == PROG_FILE_IS_DIR)
	{
		error_message = get_error_message(SHELL_NAME, error.file_name, strerror(EISDIR));
	}
	else if (error.errtype == DUP_FAIL)
	{
		error_message = get_error_message(SHELL_NAME, "dup fail", strerror(errno));
	}
	else if (error.errtype == PIPE_FAIL)
	{
		error_message = get_error_message(SHELL_NAME, "pipe fail", strerror(errno));
	}
	else if (error.errtype == EXECVE_FAIL)
	{
		error_message = get_error_message(SHELL_NAME, error.command_name, strerror(errno));
	}
	else if (error.errtype == CMD_FILE_NOT_FOUND)
	{
		error_message = get_error_message(SHELL_NAME, error.command_name, strerror(ENOENT));
	}
	else if (error.errtype == FILE_REDIR_FAIL)
	{
		error_message = get_error_message(SHELL_NAME, error.file_name, strerror(errno));
	}
	else if (error.errtype == FORK_FAIL)
	{
		error_message = get_error_message(SHELL_NAME, "fork fail", strerror(errno));
	}
	else
	{
		perror("Unspecified error");
	}
	if (error_message)
	{
		ft_putendl_fd(error_message, 2);
		free(error_message);
	}
}

void	error_and_exit(t_pipex *pipex, t_error error)
{
	t_shell	*shell;
	t_perrtypes errtype;

	errtype = error.errtype;
	print_error_message(error);
	shell = 0;
	if (pipex)
	{
		shell = (t_shell *)pipex->shell;
		ft_free_all(shell);
		shell->pipex = 0;
	}
	resolve_exit_code(errtype);
}
