// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   wrong_pipe.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/01/11 10:44:57 by chlee2            #+#    #+#             */
// /*   Updated: 2025/03/22 16:28:42 by chlee2           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// static void	handle_token(t_shell *shell, char **current_token, int *tk)
// {
// 	if (*current_token)
// 	{
// 		shell->tokens = ft_realloc(shell->tokens, sizeof(char *) * ((*tk) + 2));
// 		if (!shell->tokens)
// 			malloc_fail_clean_exit(shell);
// 		shell->tokens[(*tk)++] = *current_token;
// 		shell->tokens[*tk] = NULL;
// 		*current_token = NULL;
// 	}
// }

// static void	assign_last_token_type(t_shell *shell, char c)
// {
// 	if (c == '|')
// 		shell->last_token_type = 1;
// 	else
// 		shell->last_token_type = 2;
// }

// static void	assign_corrent_token(t_shell *shell, char **current_token, char c)
// {
// 	*current_token = str_append(shell, NULL, c);
// 	if ((c == '>' && shell->input[shell->current_index + 1] == '>')
// 		|| (c == '<' && shell->input[shell->current_index + 1] == '<'))
// 	{
// 		c = shell->input[++shell->current_index];
// 		*current_token = str_append(shell, *current_token, c);
// 	}
// }

// void	handle_wrong_pipes(t_shell *shell, char **ct, int *token_count, char c)
// {
// 	int		i;
// 	char	**new_tokens;

// 	handle_token(shell, ct, token_count);
// 	assign_corrent_token(shell, ct, c);
// 	new_tokens = malloc(sizeof(char *) * ((*token_count) + 2));
// 	if (!new_tokens)
// 		malloc_fail_clean_exit(shell);
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
// 	assign_last_token_type(shell, c);
// }
