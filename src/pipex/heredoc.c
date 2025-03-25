/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:03:34 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/25 22:26:22 by mbutuzov         ###   ########.fr       */
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

void	heredoc_readline_loop(char *eof, int fds[2], int *proper_exit)
{
	char	*line;

	line = 0;
	line = readline("> ");
	while (line)
	{
		if (!ft_strcmp(line, eof))
		{
			*proper_exit = 1;
			free(line);
			break ;
		}
		ft_putendl_fd(line, fds[1]);
		free(line);
		line = readline("> ");
	}
}

char	*get_heredoc_eof_string(char *delimiter)
{
	char	*strings[6];

	strings[0] = SHELL_NAME;
	strings[1] = ": warning: here-document at some line ";
	strings[2] = "delimited by end-of-file (wanted '";
	strings[3] = delimiter;
	strings[4] = "')\n";
	strings[5] = 0;
	return (ft_split_join(strings, 0));
}

void	in_heredoc_child(char *eof, t_shell *shell, int fds[2])
{
	int		proper_exit;
	char	*line;

	line = 0;
	proper_exit = 0;
	set_heredoc_signal();
	heredoc_readline_loop(eof, fds, &proper_exit);
	close_pipe_safe(fds);
	if (g_sig == 1)
	{
		ft_free_all(shell);
		exit(130);
	}
	if (!proper_exit)
	{
		line = get_heredoc_eof_string(eof);
		if (line)
		{
			ft_putstr_fd(line, 2);
			free(line);
		}
	}
	ft_free_all(shell);
	exit(0);
}

int	wait_heredoc(int fork_res, t_shell *shell, int fds[2])
{
	int	wait_status;
	int	wait_return;

	wait_return = wait(&wait_status);
	if (wait_return == fork_res)
	{
		set_minishell_signal();
		if (WIFEXITED(wait_status))
			shell->exit_code = WEXITSTATUS(wait_status);
		else if (WIFSIGNALED(wait_status))
			shell->exit_code = 128 + WTERMSIG(wait_status);
		if (shell->exit_code == 130)
		{
			write(2, "\n", 1);
			shell->err_code = 1;
			close(fds[0]);
			return (-1);
		}
		return (fds[0]);
	}
	close(fds[0]);
	return (-1);
}

int	get_here_doc_fd(char *eof, t_shell *shell)
{
	int		fds[2];
	int		fork_res;
	int		proper_exit;

	proper_exit = 0;
	if (pipe(fds) == -1)
		return (-1);
	before_heredoc_process_signal();
	fork_res = fork();
	if (!fork_res)
		in_heredoc_child(eof, shell, fds);
	close(fds[1]);
	if (fork_res == -1)
	{
		close(fds[0]);
		return (-1);
	}
	return (wait_heredoc(fork_res, shell, fds));
}
