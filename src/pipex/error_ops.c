/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:21:50 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/13 16:55:28 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "pipex.h"
//#include "minishell.h"
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
//void	error_and_exit(t_pipex *pipex, t_perrtypes errtype)
void	error_and_exit(t_pipex *pipex, t_perrtypes errtype, t_error error)
{
	t_shell	*shell;
//TODO: rethink, rewrite
/*
	print_error_message(*pipex, errtype);
*/
	print_error_message(error);
	shell = 0;
	perror("PIPEX ERROR");
	if (pipex)
	{
		shell = (t_shell *)pipex->shell;
//		if (shell->pipex != pipex)
//			ft_printf("problem with pipex pointer\nshell-pipex: %p\npipex: %p\n", shell->pipex, pipex);
		ft_free_all(shell);
		shell->pipex = 0;
	}
	clear_cmds(shell);
	resolve_exit_code(errtype);
}
