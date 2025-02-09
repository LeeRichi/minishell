/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:23:08 by chlee2            #+#    #+#             */
/*   Updated: 2025/02/09 18:13:47 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void finalize_token(t_shell *shell, char **current_token, int *token_count)
{
    if (*current_token)
    {
        shell->tokens = ft_realloc(shell->tokens, sizeof(char *) * (*token_count + 2));
        if (!shell->tokens)
            return;

        shell->tokens[(*token_count)++] = *current_token;
        shell->tokens[*token_count] = NULL;
        // int i = 0;
        // while(current_token[i])
        // {
        //     printf("current token: %s\n", current_token[i]);
        //     i++;
        // }
        *current_token = NULL;
        printf("finalized and value is: %d\n", shell->last_token_type);
        // shell->last_token_type = 1;
        // if (input[*i] == '|')
        // {
        //     shell->last_token_type = 1;
        // }
        // else if (input[*i] == '>' || input[*i] == '<')
        // {
        //     shell->last_token_type = 2;
        // }
        // else
        // {
        //     shell->last_token_type = 0;
        // }
    }
}

void parse_input_character(t_shell *shell, char **current_token, int *i, char *input)
{
    char *env_value;
    int j;
    char *hard_code_for_$ = "325570";

	if (input[*i] == '\'' && !(shell->in_double_quote))
        shell->in_single_quote = !(shell->in_single_quote);
    else if (input[*i] == '"' && !(shell->in_single_quote))
        shell->in_double_quote = !(shell->in_double_quote);
    else if (!(shell->in_single_quote) && input[*i] == '$')
    {
        if (strchr("\'", input[*i + 1]) || strchr("\"", input[*i + 1])) //if it's consecutive, then we should avoid the $ feature
        {
            printf("ignored dollar sign.\n"); //throw to the water
			return ;
        }
		else if (strchr(" ", input[*i + 1]))
        {
            *current_token = str_append(*current_token, '$');
        }
		else if (strchr("$", input[*i + 1])) //consecutive dollar sign //hard code
        {
            j = 0;
            while (j < 6)
            {
                *current_token = str_append(*current_token, hard_code_for_$[j]);
                j++;
            }
            (*i)++;
        }
        else
		{
			env_value = handle_dollar_sign(shell, input, i);
			if (!env_value) //if the env_value is not found, let's simply return the input str itself
			{
				printf("dollar sign with var has no value.\n"); //If no value, strjoin the rest until encounter spcae
                // return ;
			}
			else
			{
				j = 0;
				while (env_value[j])
					*current_token = str_append(*current_token, env_value[j++]);
				// free(env_value); //fuck
			}
		}
    }
    else if (strchr("|<>", input[*i]) && !(shell->in_single_quote) && !(shell->in_double_quote))
	{
        // if (input[*i] == '|')
        //     shell->last_token_type = 1;
        // else if (input[*i] == '>' || input[*i] == '<')
        //     shell->last_token_type = 2;
        // else
        //     shell->last_token_type = 0;
        // current_c = input[*i];
        // printf("current_c: %c\n", current_c);
        if (input[*i] == '<' && input[*i + 1] == '<') //valid //but maybe here should not be handle here?? figure out later
        {
            // handle_heredoc(shell, extract_delimiter(input, i));
            //do i need a break here??
            return ;
        }
        // else if (strchr("|<>", input[*i + 1])) //invalid
        // {
        //     printf("invalid consecutive\n");
        //     //put this current token + (*i + 1)char to one token, how to do it?
        // }
		shell->current_index = *i;
		handle_wrong_pipes(shell, current_token, &shell->token_count, input[*i]);
		*i = shell->current_index;
	}
    else if (strchr(WHITESPACE, input[*i]) && !(shell->in_single_quote) && !(shell->in_double_quote))
    {
        finalize_token(shell, current_token, &shell->token_count);
    }
    else
    {
        printf("input[*i]: %c\n", input[*i]);
        *current_token = str_append(*current_token, input[*i]);
    }
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

    // printf("WTF last token ty: %d\n", shell->last_token_type);

	// while (shell->last_token_type == 1 || shell->last_token_type == 2)
    while ((shell->last_token_type == 1 || shell->last_token_type == 2) && **input)
    {
    //     printf("what is the **input: %c\n", **input);
    //     printf("last token ty: %d\n", shell->last_token_type);
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

    if(!shell->tokens)
    {
        return (1);
    }
    
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
    // if (!input)
    // {
    //     printf("There is no input!!!!\n");
    //     return;
    // }
  	if (empty_pipe_checker(input, shell)) //checking case like "$ | |"
    {
		free(input);
		shell->err_code = 258;
		return;
		// exit(EXIT_FAILURE);
	}
	handle_unbalanced_quotes(&input); //checking case like '''
	parse_input_fragment(input, shell); //checking Complex scenarios with quotes, special characters, and whitespace. finally parse it to token(s)
    printf("00\n");

	//process_additional_input(shell, &input); //checking if there's un-finish quote or pipe, if yes, parse into new token(s)
    printf("1\n");
	if (empty_between_checker(shell)) //checking case like 1 | 2 | (linebreak) |    ----this is not allowed 
	{
        printf("2\n");
		free(input);
		shell->err_code = 258;
		clear_tokens(shell);
		return;
	}
    printf("3\n");
	shell->last_token_type = 0;
	free(input);
}
