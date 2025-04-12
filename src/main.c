/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:56:06 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/12 22:28:00 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_sig;

int	ft_cpy_tab(char **dest, char **src, int length)
{
	int	orig_length;

	orig_length = length;
	while (length--)
	{
		dest[length] = ft_strdup(src[length]);
		if (dest[length] == NULL)
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

void	shell_init_helper(char **envp, t_shell *shell)
{
	int	split_count;

	split_count = count_split(envp);
	shell->envp = malloc(sizeof(char *) * (split_count + 1));
	if (!shell->envp)
		malloc_fail_clean_exit(shell);
	shell->envp[split_count] = NULL;
	if (!ft_cpy_tab(shell->envp, envp, split_count))
	{
		shell->exit_code = 1;
		free(shell->envp);
		return ;
	}
}

int	shell_init(char **envp, t_shell *shell)
{
	ft_bzero(shell, sizeof(t_shell));
	shell_init_helper(envp, shell);
	if (shell->exit_code)
		malloc_fail_clean_exit(0);
	shell->stdin_fd = -1;
	shell->stdout_fd = -1;
	shell_level_ctrl(shell);
	g_sig = 0;
	if (set_minishell_signal())
	{
		ft_free_all(shell);
		exit(1);
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)av;
	if (ac != 1)
	{
		ft_putstr_fd("Usage ./minishell\n", 2);
		exit(EXIT_FAILURE);
	}
	shell_init(envp, &shell);
	while (1)
	{
		shell.input = readline(SHELL_NAME": ");
		if (!shell.input)
			break ;
		if (*shell.input)
			parse(&shell);
		else
			free(shell.input);
		execute(&shell);
		clear_tokens(&shell);
		clear_cmds(&shell);
	}
	ft_free_all(&shell);
	return (shell.exit_code);
}
