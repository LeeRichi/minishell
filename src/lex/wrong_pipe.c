/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrong_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:44:57 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/22 16:49:18 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void handle_token(t_shell *shell, char **current_token, int *token_count)
{
	if (*current_token)
	{
		shell->tokens = ft_realloc(shell->tokens, sizeof(char *) * ((*token_count) + 2));
		if (!shell->tokens)
			malloc_fail_clean_exit(shell);
		shell->tokens[(*token_count)++] = *current_token;
		shell->tokens[*token_count] = NULL;
		*current_token = NULL;
	}
}

void handle_wrong_pipes(t_shell *shell, char **current_token, int *token_count, char c)
{
	int i;
	char **new_tokens;
	
	handle_token(shell, current_token, token_count);
	*current_token = str_append(shell, NULL, c);
	if ((c == '>' && shell->input[shell->current_index + 1] == '>') ||
		(c == '<' && shell->input[shell->current_index + 1] == '<'))
		*current_token = str_append(shell, *current_token, shell->input[++shell->current_index]);
	new_tokens = malloc(sizeof(char *) * ((*token_count) + 2));
	if (!new_tokens)
		malloc_fail_clean_exit(shell);
	i = 0;
	while (i < *token_count)
	{
		new_tokens[i] = shell->tokens[i];
		i++;
	}
	free(shell->tokens);
	new_tokens[(*token_count)++] = *current_token;
	new_tokens[*token_count] = NULL;
	shell->tokens = new_tokens;
	*current_token = NULL;
	if (c == '|')
		shell->last_token_type = 1;
	else
		shell->last_token_type = 2;
}
