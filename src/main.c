/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:56:06 by chlee2            #+#    #+#             */
/*   Updated: 2025/02/26 17:00:01 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_sig	g_sig;

void shell_init(char **envp, t_shell *shell)
{
    shell->envp = envp;
	shell->envp_value_pair = NULL;
	shell->input = NULL;
	shell->tokens = NULL;
    shell->token_count = 0;
    shell->current_index = 0;
    shell->exit_code = 0;
    shell->in_single_quote = 0;
    shell->in_double_quote = 0;
    shell->err_code = 0;
    shell->last_token_type = 0;
    shell->cmds = NULL;
	shell->ambiguous_flag = 0;
	shell->stdin_fd = -1;
	shell->stdout_fd = -1;
}
/*
	params: shell
	if shell has no args - do nothing
	if shell has 1 builtin arg - preserve fds, redir, execute builtin, return fds
	otherwise execute in pipex
	execute builtin vs execute external
	make is builtin function
	if builtin, exec as builtin, always clean up resources
	call it in child or in parent
*/
// TODO: add clenup for preserved fds to shell struct
int preserve_fds(t_shell *shell)
{
	if (shell->stdin_fd == -1)
		shell->stdin_fd = dup(STDIN_FILENO);
	if (shell->stdout_fd == -1)
		shell->stdout_fd = dup(STDOUT_FILENO);
	if (shell->stdin_fd == -1 || shell->stdout_fd == -1)
	{
		ft_close(&shell->stdin_fd);
		ft_close(&shell->stdout_fd);
		return (-1);
	}
	return (0);
}

// TODO: sufficient returns?
int restore_fds(t_shell *shell)
{
	if (dup2(shell->stdin_fd, STDIN_FILENO) == -1)
		return (-1);
	if (dup2(shell->stdout_fd, STDOUT_FILENO) == -1)
		return (-1);
	return (0);
}

// builtin error handing
void execute(t_shell *shell)
{
	int	redirection_result;
	int	builtin_result;
	//ft_printf("%p\n", shell->cmds);
	if (!shell->cmds)
		return ;
	if (shell->cmds->next || !get_builtin_type(*(shell->cmds)))
	{
		pipex_launch(shell->cmds, shell->envp, shell);
	}
	else
	{
		shell->cmds->shell = shell;
		redirection_result = preserve_fds(shell);
		if (redirection_result == -1)
		{
			//TODO: error cleanup and exit?
		}
		redirection_result = process_file_redirections(shell->cmds);
		if (redirection_result == -1)
		{
			//TODO: error cleanup and exit?
		}
//TODO: pass shell as a parameter, return to exit status
		builtin_result = handle_builtin(*(shell->cmds));
		if (builtin_result == -1)
		{
			//TODO: error cleanup and exit?
		}
		redirection_result = restore_fds(shell);
		if (redirection_result == -1)
		{
			//TODO: error cleanup and exit?
		}

	}
}

// static int ft_getpid(void)
// {
// 	int fork_res;
// 	int pid_pipe[2];
// 	int wstatus;
// 	int exit_status = 1;
// 	pipe(pid_pipe);
// 	fork_res = fork();
// 	if (fork_res == -1)
// 	{
// 		close(pid_pipe[0]);
// 		close(pid_pipe[1]);
// 		return 1;
// 	}
// 	else if (fork_res)
// 	{
// 		write(pid_pipe[1], &fork_res, sizeof(fork_res));
// 		close(pid_pipe[0]);
// 		close(pid_pipe[1]);
// 		wait(&wstatus);
// 		if (WIFEXITED(wstatus))
// 				exit_status = WEXITSTATUS(wstatus);
// 			else if (WIFSIGNALED(wstatus))
// 				exit_status = 128 + WTERMSIG(wstatus);
// 		exit(exit_status);
// 	}
// 	read(pid_pipe[0], &fork_res, sizeof(fork_res));
// 	close(pid_pipe[0]);
// 	close(pid_pipe[1]);
// 	return (fork_res);
// }

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	// shell.shell_id = ft_getpid();
	(void)av;
	if (ac != 1)
	{
		printf("We only handle 1 comment.\n");
		exit(EXIT_FAILURE);
	}
	init_sig();
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, &handle_sigquit);
	shell_init(envp, &shell);
	pf_banner();
	while (1)
	{
		shell.input = readline("$ ");
		if (!shell.input) // If Ctrl+D or EOF, exit gracefully
        {
            printf("exit\n");
            break;
        }
		if (*shell.input)
			add_history(shell.input);
		parse(&shell);
// TODO: check here / check inside
		// execute(&shell);
		// cleanup shell cmds
		clear_cmds(&shell);
		// shell.cmds = 0;
		// rich Feb 25
	}
	// ft_free_all(&shell);

	return (shell.exit_code);
}
