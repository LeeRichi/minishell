/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_ops_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:42:55 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/28 18:44:23 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
