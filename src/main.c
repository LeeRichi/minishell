/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:56:06 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/24 19:58:01 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_sig;

int ft_cpy_tab(char **dest, char **src, int length)
{
	int orig_length;
	
	orig_length = length;
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

void shell_init_helper(char **envp, t_shell *shell)
{
	int split_count;

	split_count = count_split(envp);
	shell->envp = malloc(sizeof(char *) * (split_count + 1));
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
}

void shell_init(char **envp, t_shell *shell)
{
    shell->exit_code = 0;
	// TODO: use malloc_fail_clean_exit
	shell_init_helper(envp, shell);
	if (shell->exit_code)
		return;
	shell->envp_value_pair = NULL;
	shell->input = NULL;
	shell->tokens = NULL;
    shell->token_count = 0;
    shell->current_index = 0;
    shell->in_single_quote = 0;
    shell->in_double_quote = 0;
    shell->err_code = 0;
    shell->last_token_type = 0;
    shell->cmds = NULL;
	shell->ambiguous_flag = 0;
	shell->stdin_fd = -1;
	shell->stdout_fd = -1;
	shell->pipex = 0;
	shell->has_quotes = 0;
	shell_level_ctrl(shell);
}

// real one
int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	// char **env;
	// shell.shell_id = ft_getpid();
	(void)av;
	if (ac != 1)
	{
		printf("We only handle 1 argument.\n");
		exit(EXIT_FAILURE);
	}

	g_sig = 0;
	set_minishell_signal();
	// sigaction()
	// env = ft_getenv(envp);
	shell_init(envp, &shell);
	if (shell.exit_code)
		return (shell.exit_code);
	while (1)
	{
		shell.input = readline("$ ");

		// printf("fuck: %d\n", shell.exit_code);
		// if (strcmp(shell.input, "") == 0) //true
		// 	printf("test fuck\n");
		if (!shell.input) // If Ctrl+D or EOF, exit gracefully
        {
            break;
        }
		if (*shell.input)
			parse(&shell);
		else
			free(shell.input);
		// TODO: check here / check inside
		//ft_free_all(&shell);


		execute(&shell);

		//fuck
		//printf("fuck: %d\n", shell.exit_code);
		//free(shell.input);
		//shell.input = 0;
		//cleanup shell cmds
		if (shell.tokens)
		{
			free_tokens(shell.tokens);
			shell.tokens = 0;
		}
		clear_cmds(&shell);
		// shell.cmds = 0;
	}
	ft_free_all(&shell);
	return (shell.exit_code);
}

//42 big tester main
/*
int	main(int ac, char **av, char **envp)
{
	t_shell shell;
	char *line = NULL;
	(void)av;
	(void)ac;

	shell_init(envp, &shell);

	while (1)
	{
		if (isatty(fileno(stdin)))
			shell.input = readline("");
		else
		{
			line = get_next_line(fileno(stdin));
			shell.input = ft_strtrim(line, "\n");
			free(line);
		}

		if (!shell.input) // If Ctrl+D or EOF, exit gracefully
            break;

		// if (*shell.input)
		// 	add_history(shell.input);
		if (*shell.input)
			parse(&shell);
		else
			free(shell.input);

		execute(&shell);

		if (shell.tokens)
		{
			free_tokens(shell.tokens);
			shell.tokens = 0;
		}
		clear_cmds(&shell);
	}

	ft_free_all(&shell);

	// do we need it?
	// clear_history(shell.input);

	//exit
	return (shell.exit_code);
}
*/
