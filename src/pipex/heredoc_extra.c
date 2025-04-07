/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:27:43 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/04/07 19:18:19 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	set_heredoc_signal_exit(shell, fds);
	heredoc_readline_loop(eof, fds, &proper_exit);
	close_pipe_safe(fds);
	if (g_sig)
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
		if (set_minishell_signal_after_heredoc_clean(fds[0]))
			return (-1);
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

	if (pipe(fds) == -1)
		return (-1);
	if (before_heredoc_process_signal())
	{
		close_pipe_safe(fds);
		return (-1);
	}
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
