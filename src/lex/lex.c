/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:23:08 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/12 18:06:55 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	append_additional_input(t_shell *shell, char **input, char *ai)
{
	char	*spaced_input;
	char	*new_input;

	spaced_input = ft_strjoin(*input, " ");
	if (!spaced_input)
	{
		free(input);
		malloc_fail_clean_exit(shell);
	}
	new_input = ft_strjoin(spaced_input, ai);
	if (!spaced_input)
	{
		free(input);
		free(spaced_input);
		malloc_fail_clean_exit(shell);
	}
	free(*input);
	free(spaced_input);
	*input = new_input;
}

void	handle_unexpected_eof(t_shell *shell, char *input, char *ai)
{
	if (shell->last_token_type == 2)
		ft_printf_fd(STDERR, "minishell: syntax error\n");
	else
		ft_printf_fd(STDERR, "minishell: syntax error\n");
	free_matrix(shell->tokens);
	free(input);
	free(ai);
	free_matrix(shell->envp);
	exit(EXIT_FAILURE);
}

static void	invalid_checker(t_shell *shell, char *input, int err_code)
{
	if (input)
		free(input);
	shell->exit_code = STDERR;
	shell->err_code = err_code;
}

void	process_additional_input(t_shell *shell, char **input)
{
	char	*additional_input;

	while (shell->last_token_type == 1 && **input)
	{
		additional_input = readline("> ");
		if (!additional_input)
			handle_unexpected_eof(shell, *input, additional_input);
		if (ft_start_with(additional_input, '|'))
		{
			syntax_err_print(shell);
			free(additional_input);
			break ;
		}
		append_additional_input(shell, input, additional_input);
		parse_input_fragment(additional_input, shell);
		if (empty_between_checker(shell))
		{
			free(additional_input);
			invalid_checker(shell, 0, STDERR);
			return ;
		}
		free(additional_input);
	}
}

void	tokenize_input(char *input, t_shell *shell)
{	
	shell->in_single_quote = 0;
	shell->in_double_quote = 0;
	shell->expanded_ct_flag = 0;
	shell->expanded_tokens_arr = NULL;
	shell->quotes_ct_flag = 0;
	shell->quotes_tokens_arr = NULL;
	
	clear_tokens(shell);
	if (empty_pipe_checker(input, shell))
	{
		invalid_checker(shell, input, 258);
		return ;
	}
	handle_unbalanced_quotes(shell, &input);
	parse_input_fragment(input, shell);
	if (!shell->tokens)
		return ;
	if (empty_between_checker(shell))
	{
		invalid_checker(shell, input, STDERR);
		return ;
	}
	process_additional_input(shell, &input);
	if (input)
		add_history(input);
	free (input);
}
