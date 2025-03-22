/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:23:08 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/22 16:12:45 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// TODO: clear up and exit on malloc
// void finalize_token(t_shell *shell, char **current_token, int *token_count)
// {
//     size_t new_size;
//     int i;
// 	char **new_tokens;

//     if (*current_token)
//     {
//         new_size = sizeof(char *) * (*token_count + 2);
//         new_tokens = malloc(new_size);
//         if (!new_tokens)
// 			malloc_fail_clean_exit(shell);
//         i = 0;
//         while (i < *token_count)
// 		{
//             new_tokens[i] = shell->tokens[i];
//             i++;
//         }
//         new_tokens[*token_count] = *current_token;
//         new_tokens[*token_count + 1] = NULL;
//         free(shell->tokens);
//         shell->tokens = new_tokens;
//         (*token_count)++;
//         *current_token = NULL;
//     }
// }

// void handle_empty_token_strdup(t_shell *shell, char **current_token,  int *i)
// {	
// 	if (*current_token == NULL)
// 	{
// 		*current_token = ft_strdup("");
// 		if (*current_token == NULL)
// 			malloc_fail_clean_exit(shell);
// 	}
// 	(*i)++;
// }

// void handle_wave(t_shell *shell, char **current_token, int *i, char *input)
// {
// 	int j;

// 	if (input[*i + 1] == '|' || input[*i + 1] == '\0' || input[*i + 1] == ' ' || input[*i + 1] == '/')
// 	{
// 		char *home_dir = ft_getenv("HOME", shell);
// 		if (home_dir != NULL)
// 		{
// 			j = 0;
// 			while (home_dir[j++])
// 				*current_token = str_append(shell, *current_token, home_dir[j-1]);
// 			free(home_dir);
// 		}
// 		if (input[*i] == '/')
// 		{
// 			while (input[*i] != ' ' && input[*i])
// 			{
// 				*current_token = str_append(shell, *current_token, input[*i]);
// 				(*i)++;
// 			}
// 		}
// 		return ;
// 	}
// 	while (input[*i] == '~')
// 	{
// 		*current_token = str_append(shell, *current_token, '~');
// 		(*i)++;
// 	}
// 	*current_token = str_append(shell, *current_token, input[*i]);
// }

// void white_space_found_without_quote(t_shell *shell, char **current_token, int *i, char *input)
// {
// 	finalize_token(shell, current_token, &shell->token_count);
// 	if (input[*i - 1] == '|')
// 		shell->last_token_type = 1;
// 	else if (input[*i - 1] == '>' || input[*i - 1] == '<')
// 		shell->last_token_type = 2;
// 	else
// 		shell->last_token_type = 0;
// }

// void handle_consecutive_redir(t_shell *shell, char **current_token, int *i, char *input)
// {
// 	if (input[*i + 1] != '\0' && input[*i + 1] == '>')
// 	{
// 		*current_token = str_append(shell, *current_token, input[*i]);
// 		*current_token = str_append(shell, *current_token, input[*i + 1]);
// 		(*i)++;
// 	}
// 	else
// 		*current_token = str_append(shell, *current_token, input[*i]);
// 	finalize_token(shell, current_token, &shell->token_count);
// }

//TODO: check all mallocs and free and exit if the do
// void parse_input_character(t_shell *shell, char **current_token, int *i, char *input)
// {
//     if ((input[*i] == '"' && input[*i + 1] == '"') || (input[*i] == '\'' && input[*i + 1] == '\''))
//     	handle_empty_token_strdup(shell, current_token, i);
// 	else if (input[*i] == '\'' && !(shell->in_double_quote))
// 		handle_single_quote(shell, current_token, i, input);
//     else if (input[*i] == '"' && !(shell->in_single_quote))
// 		handle_double_quote(shell, current_token, i, input);
//     else if (input[*i] == '~' && !(shell->in_single_quote) && !(shell->in_double_quote))
// 		handle_wave(shell, current_token, i, input);
//     else if (!(shell->in_single_quote) && input[*i] == '$' && input[*i + 1] != '\0')
// 		massive_dollar_sign_handler(shell, current_token, i, input);
//     else if (strchr(WHITESPACE, input[*i]) && !(shell->in_single_quote) && !(shell->in_double_quote))
// 		white_space_found_without_quote(shell, current_token, i, input);
//     else if (input[*i] == '>' || input[*i] == '<')
// 		handle_consecutive_redir(shell, current_token, i, input);
//     else
//         *current_token = str_append(shell, *current_token, input[*i]);
// }

// void parse_input_fragment(char *input, t_shell *shell)
// {
//     char *current_token;
//     int i;
	
// 	i = 0;
// 	current_token = NULL;
// 	if (shell->tokens)
// 		shell->token_count = count_split(shell->tokens);
// 	else
// 		shell->token_count = 0;
//     while (input[i] != '\0')
//     {
//         parse_input_character(shell, &current_token, &i, input);
//         i++;
//     }
//     finalize_token(shell, &current_token, &shell->token_count);
// 	while(ft_strchr(WHITESPACE, input[i]))
// 		i--;
// 	if (input[i] == '|')
// 		shell->last_token_type = 1;
// 	else if (input[i] == '>' || input[i] == '<')
// 		shell->last_token_type = 2;
// 	else
// 		shell->last_token_type = 0;
// }

//TODO: check strjoins
static void append_additional_input(t_shell *shell, char **input, char *additional_input)
{
    char *spaced_input;
    char *new_input;
	
	spaced_input = ft_strjoin(*input, " ");
	if (!spaced_input)
		malloc_fail_clean_exit(shell);
	new_input = ft_strjoin(spaced_input, additional_input);
	if (!spaced_input)
		malloc_fail_clean_exit(shell);
    free(*input);
    free(spaced_input);
    *input = new_input;
}

//needs to add more
//TODO: free all before exit
void handle_unexpected_eof(t_shell *shell, char *input, char *additional_input)
{
    if (shell->last_token_type == 2)
        ft_printf_fd(STDERR, "minishell: syntax error near unexpected token `%s`\n", "|");
    else
        ft_printf_fd(STDERR, "minishell: syntax error near unexpected token `%s`\n", "|");
    free(input);
    free(additional_input);
    exit(EXIT_FAILURE);
}

void process_additional_input(t_shell *shell, char **input)
{
    char *additional_input;

    while (shell->last_token_type == 1 && **input)
    {
        additional_input = readline("> ");
        if (!additional_input || ft_start_with(additional_input, '|'))
            handle_unexpected_eof(shell, *input, additional_input);
		append_additional_input(shell, input, additional_input);
        parse_input_fragment(additional_input, shell);
        free(additional_input);
    }
}

void tokenize_input(char *input, t_shell *shell)
{
	shell->in_single_quote = 0;
	shell->in_double_quote = 0;
	clear_tokens(shell);
  	if (empty_pipe_checker(input, shell))
    {
		free(input);
        shell->exit_code = STDERR;
        shell->err_code = 258;
        return;
	}
	handle_unbalanced_quotes(shell, &input);
    parse_input_fragment(input, shell);
    if (!shell->tokens)
        return;
    if (empty_between_checker(shell))
    {
        free(input);
		shell->err_code = STDERR;
        shell->exit_code = STDERR;
        clear_tokens(shell);
        return;
    }
    process_additional_input(shell, &input);
    if (input)
		add_history(input);
    free(input);
}
