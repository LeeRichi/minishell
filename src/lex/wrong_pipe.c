/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrong_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:44:57 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/14 11:12:59 by chlee2           ###   ########.fr       */
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

int empty_pipe_checker(char *input, t_shell *shell)
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

char *contains_special_characters(const char *input)
{
	const char *special_chars[] = {">>", "<<", ">", "<", "|"};
	for (int i = 0; i < 6; i++) //to while
    {
        if (ft_strstr(input, special_chars[i]))
            return (char *)special_chars[i];
    }
    return NULL;
}

static void handle_token(t_shell *shell, char **current_token, int *token_count)
{
    if (*current_token)
    {
        shell->tokens = ft_realloc(shell->tokens, sizeof(char *) * ((*token_count) + 2));
        if (!shell->tokens)
        {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        shell->tokens[(*token_count)++] = *current_token;
        shell->tokens[*token_count] = NULL;
        *current_token = NULL;
    }
}

void handle_wrong_pipes(t_shell *shell, char **current_token, int *token_count, char c)
{
    handle_token(shell, current_token, token_count);
    *current_token = str_append(NULL, c);

    if ((c == '>' && shell->input[shell->current_index + 1] == '>') ||
        (c == '<' && shell->input[shell->current_index + 1] == '<'))
    {
        *current_token = str_append(*current_token, shell->input[++shell->current_index]); // Append the second character and increment the index
    }
    char **new_tokens = malloc(sizeof(char *) * ((*token_count) + 2));
    if (!new_tokens)
    {
        printf("malloc failed\n");
        return;
    }
    for (int i = 0; i < *token_count; i++)
    {
        new_tokens[i] = shell->tokens[i];
    }
    free(shell->tokens);
    new_tokens[(*token_count)++] = *current_token;
    new_tokens[*token_count] = NULL;
    shell->tokens = new_tokens;
    *current_token = NULL;
    shell->last_token_type = (c == '|') ? 1 : 2;
}
