/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:56:06 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/12 22:30:09 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_sig	g_sig;

int ft_cpy_tab(char **dest, char **src, int length)
{
	int orig_length = length;
	while(length--)
	{
		dest[length] = ft_strdup(src[length]);
		if (dest[length] == 0)
		{
			while (length < orig_length)
			{
				if (dest[length])
					free(dest[length]);
				length++;
			}
			return (0);
		}	
	}
	return (1);
}

void shell_init(char **envp, t_shell *shell)
{
	int split_count = count_split(envp);
	//printf("split count: %d\n", split_count);
	shell->envp = malloc(sizeof(char *) * (split_count + 1));
	//print_tokens(envp);
	if (!shell->envp)
	{
		shell->exit_code = 1;
		return ;
	}
	shell->envp[split_count] = 0;
	if (!ft_cpy_tab(shell->envp, envp, split_count))
	{
		shell->exit_code = 1;
		free(shell->envp);
		return ;
	}
//	print_tokens(shell->envp);
	//printf("shell->envp pointer (shell init): %p\n", shell->envp);
	/*
	int i = 0;
	while(i < split_count)
	{
		printf("little ptr:", i, &shell->envp[i]);
		i++;		
	}
	*/

	
    //shell->envp = envp;
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
	shell->pipex = 0;
	shell_level_ctrl(shell);
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
	// char **env;
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
	// env = ft_getenv(envp);
	shell_init(envp, &shell);

	//cmd out when running tester
	// pf_banner();
	while (1)
	{
		shell.input = readline("$ ");
		
		// printf("fuck: %d\n", shell.exit_code);
		// if (strcmp(shell.input, "") == 0) //true
		// 	printf("test fuck\n");
		if (!shell.input) // If Ctrl+D or EOF, exit gracefully
        {
            printf("exit\n");
            break;
        }
		if (*shell.input)
			add_history(shell.input);
		if (*shell.input)
			parse(&shell);
		else
			free(shell.input);
// TODO: check here / check inside
		//ft_free_all(&shell);
		execute(&shell);
//		free(shell.input);
//		shell.input = 0;
		// cleanup shell cmds
		if (shell.tokens)
		{
			free_tokens(shell.tokens);
			shell.tokens = 0;
		}
		
		clear_cmds(&shell);
		// shell.cmds = 0;
	}
	// ft_free_all(&shell);

	return (shell.exit_code);
}
