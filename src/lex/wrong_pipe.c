/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrong_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:44:57 by chlee2            #+#    #+#             */
/*   Updated: 2025/02/18 17:56:40 by chlee2           ###   ########.fr       */
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

//handle different amount of >>>>> or <<<<<<<<< (weird) (hard code)
// void ft_tail_checker(char *str)
// {
//     int consecutive_in = 0;
//     int consecutive_out = 0;
//     int i = 0;

//     while(str[i])
//     {
//         if (str[i] == '<') {
//             consecutive_in++;
//             consecutive_out = 0;
//         } else if (str[i] == '>') {
//             consecutive_out++;
//             consecutive_in = 0;
//         } else {
//             consecutive_in = 0;
//             consecutive_out = 0;
//         }
//         i++;
//     }
// 	printf("in: %d\n", consecutive_in);
// 	printf("out: %d\n", consecutive_out);
//     if (consecutive_in == 4) {
//         printf("minishell: syntax error near unexpected token `%s`\n", "<");
//         return;
//     }
//     else if (consecutive_in == 5) {
//         printf("minishell: syntax error near unexpected token `%s`\n", "<<");
//         return;
//     }
//     else if (consecutive_in > 5) {
//         printf("minishell: syntax error near unexpected token `%s`\n", "<<<");
//         return;
//     }
//     else if (consecutive_out >= 3) {
// 		printf("old_str: %s\n", str);
// 		char *new_str = ft_strstr(str, ">>");
// 		printf("new_str: %s\n", new_str += 2);
//         if (consecutive_out >= 4)
//             printf("minishell: syntax error near unexpected token `%c%c`\n", new_str[0], new_str[1]);
//         else
// 		    printf("minishell: syntax error near unexpected token `%c`\n", new_str[0]);
// 		return;
//     }
//     printf("minishell: syntax error near unexpected token `%s`\n", "newline");
// }

int empty_pipe_checker(char *input, t_shell *shell)
{
	while (*input == ' ' || *input == '\t' || *input == '\n')
		input++;

    if (ft_strncmp(input, "||", 2) == 0)
    {
        printf("minishell: syntax error near unexpected token `%s`\n", "||");
        clear_tokens(shell);
        return (1);
    }
    if (ft_start_with(input, '|'))
    {
        printf("minishell: syntax error near unexpected token `%c`\n", '|');
        clear_tokens(shell);
        return (1);
    }
	if (ft_end_with(input, '>') || ft_end_with(input, '<'))
	{
        // ft_tail_checker(input);
		printf("minishell: syntax error near unexpected token `%s`\n", "newline");
		clear_tokens(shell);
		return (1);
	}
	if(is_exact_operator(input))
	{
		printf("minishell: syntax error near unexpected token `%s`\n", "newline");
		clear_tokens(shell);
		return (1);
    }
    return (0);
}

char *contains_special_characters(const char *input)
{
	const char *special_chars[] = {">>", "<<", ">", "<", "|"};
	for (int i = 0; i < 6; i++)
    {
        if (ft_strstr(input, special_chars[i]))
            return (char *)special_chars[i];
    }
    return NULL;
}

// 	if ((first_nid = contains_special_characters(input)))
//     {
//         new_str = ft_strstr(input, first_nid) + 1;

// 		if (new_str)
// 		{
//             if((err_nid = ft_start_with_specials(new_str)))
// 			{
// 				printf("minishell: syntax error near unexpected token `%s'\n", err_nid);
//         		clear_tokens(shell);
// 				return (1);
// 			}
//         }
//     }
//     return 0;
// }

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
    // int i = 0;

	// Handle the pipe or redirection
	handle_token(shell, current_token, token_count);

	*current_token = str_append(NULL, c);

	if ((c == '>' && shell->input[shell->current_index + 1] == '>') ||
        (c == '<' && shell->input[shell->current_index + 1] == '<'))
    {
        *current_token = str_append(*current_token, shell->input[++shell->current_index]); // Append the second character and increment the index
    }

	shell->tokens = ft_realloc(shell->tokens, sizeof(char *) * ((*token_count) + 2));
    if (!shell->tokens)
		printf("realloc failed\n"); //more like realloc fail
	// if (!shell->tokens)
	// 	printf("wait for more input\n");
	shell->tokens[(*token_count)++] = *current_token;
	shell->tokens[*token_count] = NULL;
	*current_token = NULL;

	shell->last_token_type = (c == '|') ? 1 : 2;
}
