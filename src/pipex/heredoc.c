/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:03:34 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/29 20:31:49 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fd_safe(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

void	close_pipe_safe(int fds[2])
{
	close_fd_safe(fds);
	close_fd_safe(fds + 1);
}

int	check_heredoc(t_cmd cmd)
{
	size_t	infile_count;
	size_t	outfile_count;
	size_t	count;

	count = 0;
	if (cmd.infiles)
		infile_count = (size_t)count_split(cmd.infiles);
	else
		infile_count = 0;
	if (cmd.outfiles)
		outfile_count = (size_t)count_split(cmd.outfiles);
	else
		outfile_count = 0;
	if (!infile_count)
		return (0);
	while (count < infile_count + outfile_count)
	{
		if (cmd.redirect_type[count] == HERE_DOC)
			return (1);
		count++;
	}
	return (0);
}

int	try_get_heredoc(size_t count, t_cmd cmd)
{
	char	*heredoc_eof;
	int		fd;

	heredoc_eof = get_redir_str(count, cmd);
	fd = get_here_doc_fd(heredoc_eof, (t_shell *)cmd.shell);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	get_cmd_heredoc(t_cmd cmd)
{
	int		fd;
	size_t	count;
	size_t	file_count;

	file_count = count_files(&cmd);
	fd = -1;
	count = 0;
	while (count < file_count)
	{
		if (cmd.redirect_type[count] == HERE_DOC)
		{
			if (fd != -1)
				close(fd);
			fd = try_get_heredoc(count, cmd);
			if (fd == -1)
				return (-1);
		}
		count++;
	}
	return (fd);
}
