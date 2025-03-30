/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrong_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:44:57 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/30 19:35:26 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	handle_token(t_shell *shell, char **ct, int *tc)
// {
// 	if (*ct)
// 	{
// 		shell->tokens = ft_realloc(shell->tokens, sizeof(char *) * ((*tc) + 2));
// 		if (!shell->tokens)
// 		{
// 			if (*ct)
// 				free(*ct);
// 			malloc_fail_clean_exit(shell);
// 		}
// 		shell->tokens[(*tc)++] = *ct;
// 		shell->tokens[*tc] = NULL;
// 		*ct = NULL;
// 	}
// }

// static void	ltt_inject(t_shell *shell, char c)
// {
// 	if (c == '|')
// 		shell->last_token_type = 1;
// 	else
// 		shell->last_token_type = 2;
// }

// void	handle_wrong_pipes(t_shell *shell, char **ct, int *token_count, char c)
// {
// 	int		i;
// 	char	**new_tokens;

// 	handle_token(shell, ct, token_count);
// 	*ct = str_append(shell, NULL, c);
// 	if ((c == '>' && shell->input[shell->current_index + 1] == '>')
// 		|| (c == '<' && shell->input[shell->current_index + 1] == '<'))
// 		*ct = str_append(shell, *ct, shell->input[++shell->current_index]);
// 	new_tokens = malloc(sizeof(char *) * ((*token_count) + 2));
// 	if (!new_tokens)
// 	{
// 		free (*ct);
// 		malloc_fail_clean_exit(shell);
// 	}
// 	i = 0;
// 	while (i < *token_count)
// 	{
// 		new_tokens[i] = shell->tokens[i];
// 		i++;
// 	}
// 	free(shell->tokens);
// 	new_tokens[(*token_count)++] = *ct;
// 	new_tokens[*token_count] = NULL;
// 	shell->tokens = new_tokens;
// 	*ct = NULL;
// 	ltt_inject(shell, c);
// }
