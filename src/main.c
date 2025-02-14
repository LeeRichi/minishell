/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:56:06 by chlee2            #+#    #+#             */
/*   Updated: 2025/02/14 19:31:43 by mbutuzov         ###   ########.fr       */
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

// builtin error handing 
void execute(t_shell *shell)
{
	ft_printf("%p\n", shell->cmds);
	if (!shell->cmds)
		return ;
	if (shell->cmds->next || !is_builtin(shell->cmds))
		pipex_launch(shell->cmds, shell->envp);
	else
	{
		preserve_fds(shell);
		

	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

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
	}
	ft_free_all(&shell);
	return (shell.exit_code);
}
