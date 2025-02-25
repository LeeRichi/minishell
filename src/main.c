/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:56:06 by chlee2            #+#    #+#             */
/*   Updated: 2025/02/25 22:28:37 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_sig	g_sig;

void shell_init(char **envp, t_shell *shell)
{
    shell->envp = envp;
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
		execute(&shell);
		// cleanup shell cmds
		shell.cmds = 0;
	}
	// ft_free_all(&shell);

	return (shell.exit_code);
}
