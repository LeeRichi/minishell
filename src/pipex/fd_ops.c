/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_ops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:24:34 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/28 18:48:57 by mbutuzov         ###   ########.fr       */
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
