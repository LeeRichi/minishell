/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:03:34 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/24 19:58:04 by mbutuzov         ###   ########.fr       */
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
/*

int is_eof_with_nl(char *line, char *eof)
{
	size_t eof_length;

	eof_length = ft_strlen(eof);
	if (ft_strncmp(eof, line, eof_length))
		return (0);
	line += eof_length;
	if (*line == '\n' && *(line + 1) == 0)
		return (1);
	return (0);
}

*/
int check_heredoc(t_cmd cmd)
{
	size_t infile_count;
	size_t outfile_count;
	size_t count;

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

int get_cmd_heredoc(t_cmd cmd)
{
	int fd;
	size_t infile_count;
	size_t outfile_count;
	size_t count;
	char *heredoc_eof;

	fd = -1;
	count = 0;
	if (cmd.infiles)
		infile_count = (size_t)count_split(cmd.infiles);
	else
		infile_count = 0;
	if (cmd.outfiles)
		outfile_count = (size_t)count_split(cmd.outfiles);
	else
		outfile_count = 0;
	while (count < infile_count + outfile_count)
	{
		if (cmd.redirect_type[count] == HERE_DOC)
		{
			if (fd != -1)
			{
				close(fd);
				heredoc_eof = get_redir_str(count, cmd);
// TODO: check shell cleanup in child process
				fd = get_here_doc_fd(heredoc_eof, (t_shell *)cmd.shell);
				if (fd == -1)
					return (-1);
			}
			else
			{
				heredoc_eof = get_redir_str(count, cmd);
				fd = get_here_doc_fd(heredoc_eof, (t_shell *)cmd.shell);
				if (fd == -1)
					return (-1);
			}
		}
		count++;
	}
	return (fd);
}

void print_line_ascii(char *line)
{
	if (!line)
		return ;
	while(*line)
	{
		ft_putnbr_fd(*line, 2);
		write(2, "\n", 1);
		line++;
	}
}

int get_here_doc_fd(char *eof, t_shell *shell)
{
	//int fork_res;
	int fds[2];
	int fork_res;
	char *line;
//	int dup_res;
	int proper_exit;

	line = 0;
	proper_exit = 0;
//	char *fineof;
	if (pipe(fds) == -1)
		return (-1);
//	before_child_process_signal();
	before_heredoc_process_signal();
	fork_res = fork();
	if (!fork_res)
	{
		set_heredoc_signal();
		line = readline("> ");
		while (line)
		{
			if (!ft_strcmp(line, eof))
			{
				proper_exit = 1;
				free(line);
				break ;
			}
			ft_putendl_fd(line, fds[1]);
			free(line);
			line = readline("> ");
		}
		close_pipe_safe(fds);
		if (g_sig == 1)
		{
			ft_free_all(shell);
			exit(130);
		}
		if (!proper_exit)
		{
//			bash: warning: here-document at some line delimited by end-of-file (wanted `wow')
//TODO: adjust to be correct error message
//			ft_putstr_fd("\nheredoc EOF stoped\n", 2);
			if (!dup2(2, 1))
				printf("%s: warning: here-document at some line delimited by end-of-file (wanted '%s')\n", SHELL_NAME, eof);
		}
		ft_free_all(shell);
		exit(0);
	}
	close(fds[1]);
	if (fork_res == -1)
	{
		close(fds[0]);
		return (-1);
	}
/*
	if (waitpid(fork_res, 0, 0) == fork_res)
		return (fds[0]);
*/
	int wait_status;
	int wait_asd  = wait(&wait_status);
//	if (wait(&wait_status) == fork_res)
	if (wait_asd == fork_res)
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
/*
int main()
{
	int somefd = get_here_doc_fd("some");
	if (somefd == -1)
		return (1);
	close(somefd);
	return (0);
	char *line = get_next_line(somefd);
	while (line)
	{
		ft_printf(line);
		free(line);
		line = get_next_line(somefd);
	}
	close(somefd);
	return (0);
}
*/
