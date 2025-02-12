/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:03:34 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/02/12 22:01:07 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"
#include "../../includes/minishell.h"
#include "sys/wait.h"
#include "stdio.h"
//wip

int ft_strcmp(const char *s1, const char *s2)
{
	int s1_length;
	int s2_length;

	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	if (s1_length > s2_length)
		return (ft_strncmp(s1, s2, s1_length));
	return (ft_strncmp(s1, s2, s2_length));
}

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

	eof_length = ft_strlen(eof)
	if (ft_strncmp(eof, line, eof_length))
		return (1);
	line += eof_length;
	if (*line == '\n')
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
	infile_count = (size_t)count_split(cmd.infiles);
	outfile_count = (size_t)count_split(cmd.outfiles);
	while (count < infile_count + outfile_count)
	{
		if (cmd.redirect_type[count] == HERE_DOC)
		{
			if (fd != -1)
			{
				close(fd);
				heredoc_eof = get_redir_str(count, cmd);
				fd = get_here_doc_fd(heredoc_eof);
				if (fd == -1)
					return (-1);
			}
			else
			{
				heredoc_eof = get_redir_str(count, cmd);
				fd = get_here_doc_fd(heredoc_eof);
				if (fd == -1)
					return (-1);
			}
		}
		count++;
	}
	return (fd);
}

int get_here_doc_fd(char *eof)
{
	//int fork_res;
	int fds[2];
	int fork_res;
	char *line;
	int dup_res;
	char *fineof;
	if (pipe(fds) == -1)
		return (-1);
	fork_res = fork();
	if (!fork_res)
	{
		dup_res = dup2(fds[1], 1);
		fineof = ft_strjoin(eof, "\n");
		close_pipe_safe(fds);
//		close(fds[1]);
//		close(fds[0]);
		if (!fineof)
			exit(1);
		if (dup_res == -1)
		{
			perror("dup error");
			free(fineof);
			exit(1);
		}
	// TODO: check write, cleanup on fail
		write(0, "> ", 2);
		line = get_next_line(0);
		while (line)
		{
			if (!ft_strcmp(line, fineof))
			{
				free(line);
				break ;
			}
			ft_printf("%s", line);
	// TODO: check write, cleanup on fail
			write(0, "> ", 2);
			free(line);
			line = get_next_line(0);
		}
		free(fineof);
		get_next_line(-1);
/*
		TODO: cleanup everything
*/
		exit(0);
	}
	close(fds[1]);
	if (fork_res == -1)
	{
		close(fds[0]);
		return (-1);
	}
	if (waitpid(fork_res, 0, 0) == fork_res)
		return (fds[0]);
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
