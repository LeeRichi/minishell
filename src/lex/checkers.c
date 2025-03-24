/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:39:06 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/24 12:44:26 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int is_exact_operator(char *input)
{
	char *trimmed_input;
	int result;

	result = 0;
	trimmed_input = ft_strtrim(input, " \t\n");
	if (!trimmed_input)
		return (0);
	if ((ft_strncmp(trimmed_input, ">", 1) == 0 && ft_strlen(trimmed_input) == 1) ||
		(ft_strncmp(trimmed_input, ">>", 2) == 0 && ft_strlen(trimmed_input) == 2) ||
		(ft_strncmp(trimmed_input, "<", 1) == 0 && ft_strlen(trimmed_input) == 1) ||
		(ft_strncmp(trimmed_input, "<<", 2) == 0 && ft_strlen(trimmed_input) == 2))
		result = 1;
	free(trimmed_input);
	return result;
}

int	empty_pipe_checker(char *input, t_shell *shell)
{
	while (*input == ' ' || *input == '\t' || *input == '\n')
		input++;
	if (ft_strncmp(input, "||", 2) == 0)
	{
		ft_printf_fd(STDERR, "minishell: syntax error near unexpected token `hi`\n", "||");
		clear_tokens(shell);
		shell->exit_code = 2;
		return (1);
	}
	if (ft_start_with(input, '|'))
	{
		ft_printf_fd(STDERR, "minishell: syntax error near unexpected token `%s`\n", "|");
		clear_tokens(shell);
		shell->exit_code = 2;
		return (1);
	}
	if (ft_end_with(input, '>') || ft_end_with(input, '<'))
	{
		ft_printf_fd(STDERR, "minishell: syntax error near unexpected token `hi`\n", "newline");
		clear_tokens(shell);
		shell->exit_code = 2;
		return (1);
	}
	if(is_exact_operator(input))
	{
		ft_printf_fd(STDERR, "minishell: syntax error near unexpected token `hi`\n", "newline");
		clear_tokens(shell);
		shell->exit_code = 2;
		return (1);
	}
	return (0);
}

int	empty_between_checker(t_shell *shell)
{
	int	i;

	if(!shell->tokens)
		return (1);
	i = 0;
	while (shell->tokens[i])
	{
		if ((strcmp(shell->tokens[i], "|") == 0 && strcmp(shell->tokens[i + 1], "|") == 0))
		{
			if (shell->tokens[i + 1] && shell->ambiguous_flag != 1)
			{
				ft_printf_fd(STDERR, "minishell: syntax error near unexpected token `fuck`\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

// int	empty_between_checker(t_shell *shell)
// {
// 	int	i;
// 	char *message;

// 	message = "minishell: syntax error near unexpected token";
// 	if(!shell->tokens)
// 		return (1);
// 	i = 0;
// 	while (shell->tokens[i])
// 	{
// 		if ((strcmp(shell->tokens[i], "|") == 0 && strcmp(shell->tokens[i + 1], "|") == 0))
// 		{
// 			if (shell->tokens[i + 1] && shell->ambiguous_flag != 1)
// 			{
// 				ft_printf_fd(STDERR, "%s `%d`\n", message, "|");
// 				return (1);
// 			}
// 		}
// 		i++;
// 	}
// 	return (0);
// }
