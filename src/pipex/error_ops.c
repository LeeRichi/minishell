/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:21:50 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/12/10 13:18:54 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	resolve_exit_code(t_perrtypes errtype)
{
	if (errtype == CMD_NOT_FOUND || errtype == CMD_FILE_NOT_FOUND)
		exit(127);
	if (errtype == EXECVE_FAIL || errtype == PROG_FILE_IS_DIR)
		exit(126);
	exit(EXIT_FAILURE);
}

static void	write_smth_with_colon_fd(char *smth, int fd)
{
	ft_putstr_fd(smth, fd);
	ft_putstr_fd(": ", fd);
}

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

void	error_and_exit(t_pipex *pipex, t_perrtypes errtype)
{
	print_error_message(*pipex, errtype);
	if (pipex)
		free_all(*pipex);
	resolve_exit_code(errtype);
}
