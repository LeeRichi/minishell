/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:39:06 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/04 16:17:06 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_exact_operator(char *input)
{
	char	*trimmed_s;
	int		result;

	result = 0;
	trimmed_s = ft_strtrim(input, " \t\n");
	if (!trimmed_s)
		return (0);
	if ((ft_strncmp(trimmed_s, ">", 1) == 0 && ft_strlen(trimmed_s) == 1)
		|| (ft_strncmp(trimmed_s, ">>", 2) == 0 && ft_strlen(trimmed_s) == 2)
		|| (ft_strncmp(trimmed_s, "<", 1) == 0 && ft_strlen(trimmed_s) == 1)
		|| (ft_strncmp(trimmed_s, "<<", 2) == 0 && ft_strlen(trimmed_s) == 2))
		result = 1;
	free(trimmed_s);
	return (result);
}

int	syntax_err_print(t_shell *shell)
{
	ft_printf_fd(STDERR, "minishell: syntax error\n");
	clear_tokens(shell);
	shell->exit_code = 2;
	return (1);
}

int	empty_pipe_checker(char *input, t_shell *shell)
{
	while (*input == ' ' || *input == '\t' || *input == '\n')
		input++;
	if (ft_strncmp(input, "||", 2) == 0
		|| ft_start_with(input, '|')
		|| ft_end_with(input, '>')
		|| ft_end_with(input, '<')
		|| is_exact_operator(input))
		return (syntax_err_print(shell));
	return (0);
}

int	empty_between_checker(t_shell *shell)
{
	int	i;

	if (!shell->tokens)
		return (1);
	i = 0;
	while (shell->tokens[i])
	{
		if ((ft_strcmp(shell->tokens[i], "|") == 0
				&& shell->tokens[i + 1]
				&& ft_strcmp(shell->tokens[i + 1], "|") == 0))
		{
			if (shell->tokens[i + 1] && shell->ambiguous_flag != 1)
			{
				ft_printf_fd(STDERR, "minishell: syntax error\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}
