/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_fragment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:43:40 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/07 16:36:15 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	finalize_token(t_shell *shell, char **ct, int *token_count, char *s)
{
	size_t	new_size;
	int		i;
	char	**new_tokens;

	if (*ct)
	{
		new_size = sizeof(char *) * (*token_count + 2);
		new_tokens = malloc(new_size);
		if (!new_tokens)
			malloc_fail_clean_exit_v3(shell, s, *ct);
		i = 0;
		while (i < *token_count)
		{
			new_tokens[i] = shell->tokens[i];
			i++;
		}
		new_tokens[*token_count] = *ct;
		new_tokens[*token_count + 1] = NULL;
		free(shell->tokens);
		shell->tokens = new_tokens;
		(*token_count)++;
		*ct = NULL;
	}
}

void	parse_input_fragment(char *input, t_shell *shell)
{
	char	*current_token;
	int		i;

	i = 0;
	current_token = NULL;
	if (shell->tokens)
		shell->token_count = count_split(shell->tokens);
	else
		shell->token_count = 0;
	while (input[i] != '\0')
	{
		parse_input_character(shell, &current_token, &i, input);
		if (input[i] == 0)
			break ;
		i++;
	}
	finalize_token(shell, &current_token, &shell->token_count, input);
	while (i > 0 && ft_strchr(WHITESPACE, input[i]))
		i--;
	if (input[i] == '|')
		shell->last_token_type = 1;
	else if (input[i] == '>' || input[i] == '<')
		shell->last_token_type = 2;
	else
		shell->last_token_type = 0;
}
