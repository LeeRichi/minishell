/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_ops_extra_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:45:29 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/28 18:47:40 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
