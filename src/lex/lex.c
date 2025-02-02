/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:23:08 by chlee2            #+#    #+#             */
/*   Updated: 2025/01/17 19:49:47 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void finalize_token(t_shell *shell, char **current_token, int *token_count)
{
    if (*current_token)
    {
        shell->tokens = ft_realloc(shell->tokens, sizeof(char *) * (*token_count + 2));
        shell->tokens[(*token_count)++] = *current_token;
        shell->tokens[*token_count] = NULL;
        *current_token = NULL;
        shell->last_token_type = 1;
    }
}

void parse_input_character(t_shell *shell, char **current_token, int *i, char *input)
{
    char *env_value;
    int j;

	if (input[*i] == '\'' && !(shell->in_double_quote))
        shell->in_single_quote = !(shell->in_single_quote);
    else if (input[*i] == '"' && !(shell->in_single_quote))
        shell->in_double_quote = !(shell->in_double_quote);
    else if (!(shell->in_single_quote) && input[*i] == '$')
    {
        env_value = handle_dollar_sign(input, i);
        j = 0;
        while (env_value[j])
            *current_token = str_append(*current_token, env_value[j++]);
        free(env_value);
    }
    else if (strchr("|<>", input[*i]) && !(shell->in_single_quote) && !(shell->in_double_quote))
	{
        if (input[*i] == '<' && input[*i + 1] == '<')
        {
            handle_heredoc(shell, extract_delimiter(input, i));
            //do i need a break here??
            return ;
        }
		shell->current_index = *i;
		handle_wrong_pipes(shell, current_token, &shell->token_count, input[*i]);
		*i = shell->current_index;
	}
    else if (strchr(WHITESPACE, input[*i]) && !(shell->in_single_quote) && !(shell->in_double_quote))
        finalize_token(shell, current_token, &shell->token_count);
    else
        *current_token = str_append(*current_token, input[*i]);
}

void parse_input_fragment(char *input, t_shell *shell)
{
    char *current_token = NULL;
    int i = 0;
	shell->token_count = shell->tokens ? ft_arraylen(shell->tokens) : 0;

    while (input[i] != '\0')
    {
        parse_input_character(shell, &current_token, &i, input);
        i++;
    }
    finalize_token(shell, &current_token, &shell->token_count);
}

static void append_additional_input(char **input, char *additional_input)
{
    char *spaced_input = ft_strjoin(*input, " ");
    char *new_input = ft_strjoin(spaced_input, additional_input);
    free(*input);
    free(spaced_input);
    *input = new_input;
}

//needs to add more
void handle_unexpected_eof(t_shell *shell, char *input, char *additional_input)
{
    if (shell->last_token_type == 2)
        printf("minishell: syntax error near unexpected token `%c`\n", '|');
    else
        printf("minishell: syntax error near unexpected token `%c`\n", '<');
    free(input);
    free(additional_input);
    exit(EXIT_FAILURE);
}

void process_additional_input(t_shell *shell, char **input)
{
    char *additional_input;

	while (shell->last_token_type == 2 || shell->last_token_type == 3)
    {
        printf("> ");
        additional_input = readline(NULL);
        if (!additional_input || ft_start_with(additional_input, '|'))
            handle_unexpected_eof(shell, *input, additional_input);
		append_additional_input(input, additional_input);
        parse_input_fragment(additional_input, shell);
        free(additional_input);
    }
}

//removed "|" from the sets
static char *ft_start_with_specials_v2(char *str)
{
	int i;
	int j;
	size_t len;;
	const char **special_chars;

	special_chars = (const char *[]){">>", "<<", ">", "<", NULL};
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	j = 0;
	while (special_chars[j] != NULL)
	{
		len = strlen(special_chars[j]);
		if (strncmp(&str[i], special_chars[j], len) == 0)
			return ((char *)special_chars[j]);
        j++;
    }

    return NULL;
}

int empty_between_checker(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->tokens[i])
	{
		if (ft_start_with_specials_v2(shell->tokens[i]) ||
    		(strcmp(shell->tokens[i], "|") == 0 && strcmp(shell->tokens[i + 1], "|") == 0))
		{
			if (ft_start_with_specials(shell->tokens[i + 1]))
			{
        		printf("minishell: syntax error near unexpected token `%s`\n", ft_start_with_specials(shell->tokens[i + 1]));
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void tokenize_input(char *input, t_shell *shell)
{
	shell->in_single_quote = 0;
	shell->in_double_quote = 0;
	clear_tokens(shell);
  	if (empty_pipe_checker(input, shell))
    {
        free(input);
		shell->err_code = 258;
		return;
		// exit(EXIT_FAILURE);
	}
	handle_unbalanced_quotes(&input);
	parse_input_fragment(input, shell);
	process_additional_input(shell, &input);
	if (empty_between_checker(shell))
	{
		free(input);
		shell->err_code = 258;
		clear_tokens(shell);
		return;
	}
	shell->last_token_type = 0;
	free(input);
}
