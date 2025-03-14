/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:23:08 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/10 22:23:55 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void finalize_token(t_shell *shell, char **current_token, int *token_count)
{
    size_t new_size;
    int i;
	char **new_tokens; 
    
    if (*current_token)
    {
        new_size = sizeof(char *) * (*token_count + 2);
        new_tokens = malloc(new_size);
        if (!new_tokens)
            return;
        i = 0;
        while (i < *token_count)
		{
            new_tokens[i] = shell->tokens[i];
            i++;
        }
        new_tokens[*token_count] = *current_token;
        new_tokens[*token_count + 1] = NULL;
        free(shell->tokens);
        shell->tokens = new_tokens;
        (*token_count)++;
        *current_token = NULL;
    }
}

void parse_input_character(t_shell *shell, char **current_token, int *i, char *input)
{
    char *env_value;
    int j;
    char *id_as_str;
    int str_len;
	char *itoaed_str;

    //put an empty str into token
    if (input[*i] == '"' && input[*i + 1] == '"')
    {
        // printf("Caught empty string inside double quotes!\n");
        if (*current_token == NULL)
            *current_token = strdup("");
        (*i)++;
    }
	else if (input[*i] == '\'' && !(shell->in_double_quote))
        shell->in_single_quote = !(shell->in_single_quote);
    else if (input[*i] == '"' && !(shell->in_single_quote))
        shell->in_double_quote = !(shell->in_double_quote);
    else if (input[*i] == '~' && !(shell->in_single_quote) && !(shell->in_double_quote)) //later write into it's own helper function. ex: handle_wave_sign()
    {
		if (input[*i + 1] == '|' || input[*i + 1] == '\0' || input[*i + 1] == ' ' || input[*i + 1] == '/')
		{
			const char *home_dir = ft_getenv("HOME", shell);
			if (home_dir != NULL)
			{
				j = 0;
				while (home_dir[j++])
					*current_token = str_append(*current_token, home_dir[j-1]);
			}
			(*i)++;
            if (input[*i] == '/')
            {
                while (input[*i] != ' ' && input[*i])
                {
                    *current_token = str_append(*current_token, input[*i]);
                    (*i)++;
                }
            }
			return ;
		}
		while (input[*i] == '~')
		{
			*current_token = str_append(*current_token, '~');
			(*i)++;
		}
    }
    else if (!(shell->in_single_quote) && input[*i] == '$' && input[*i + 1] != '\0')
    {
	    if (strchr("$", input[*i + 1]) && input[*i + 1] != '\0') //consecutive dollar sign //todo
        {
            // printf("input[*i]: %c, input[*i + 1]: %c\n", input[*i], input[*i + 1]);
            id_as_str = ft_itoa(shell->shell_id);
            str_len = ft_strlen(id_as_str);
            j = 0;
            while(j < str_len)
            {
                *current_token = str_append(*current_token, id_as_str[j]);
                j++;
            }
            (*i) += 2;
            while(input[*i] == '$')
            {
                *current_token = str_append(*current_token, '$');
                (*i)++;
            }
        }
        else if (strchr("?", input[*i + 1]))
        {
            // printf("input[*i]: %c, input[*i + 1]: %c\n", input[*i], input[*i + 1]);
            // printf("hi: %d", shell->exit_code);
            
			itoaed_str = ft_itoa(shell->exit_code);
            
			int j = 0;
			while(itoaed_str[j])
			{
				*current_token = str_append(*current_token, itoaed_str[j]);
				j++;
			}

			(*i)++;
            // while (input[*i] && !strchr(" ", input[*i + 1])) //echo $?
			// {
			// 	printf("hiiiii\n");
			// 	(*i)++;
			// }
        }
        else if ((strchr("\'", input[*i + 1]) && shell->in_single_quote) || (strchr("\"", input[*i + 1]) && shell->in_double_quote)) //if it's consecutive, then we should avoid the $ feature
        {
			*current_token = str_append(*current_token, '$');
            // printf("ignored dollar sign.\n"); //throw to the water
			return ;
        }
		else if (strchr(" ", input[*i + 1]))
        {
            *current_token = str_append(*current_token, '$');
        }
        else
		{
			env_value = handle_dollar_sign(shell, input, i);
			if (!env_value) //asign '\0' for the tokens who does have value
            {
				return ;
				// *current_token = str_append(*current_token, '\0');
            }
			else
			{
				j = 0;
				while (env_value[j])
					*current_token = str_append(*current_token, env_value[j++]);
			}
            free(env_value);
		}
    }
    else if (strchr("|<>", input[*i]) && !(shell->in_single_quote) && !(shell->in_double_quote))
	{
        if (input[*i] == '|')
            shell->last_token_type = 1;
        else if (input[*i] == '>' || input[*i] == '<')
            shell->last_token_type = 2;
        else if (input[*i] == '<' && input[*i + 1] == '<') //valid //but maybe here should not be handle here?? figure out later
        {
            shell->last_token_type = 3;
            // handle_heredoc(shell, extract_delimiter(input, i));
            //do i need a break here??
            return ;
        }
        else
            shell->last_token_type = 0;
		shell->current_index = *i;
		handle_wrong_pipes(shell, current_token, &shell->token_count, input[*i]);
		*i = shell->current_index;
	}
    else if (strchr(WHITESPACE, input[*i]) && !(shell->in_single_quote) && !(shell->in_double_quote))
    {
        finalize_token(shell, current_token, &shell->token_count);
        if (input[*i - 1] == '|')
            shell->last_token_type = 1;
        else if (input[*i - 1] == '>' || input[*i - 1] == '<')
            shell->last_token_type = 2;
        else
            shell->last_token_type = 0;
    }
    else
    {
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
    //fuck
    finalize_token(shell, &current_token, &shell->token_count);
    //if the last parsed char is one of the below
	while(strchr(WHITESPACE, input[i]))
		i--;
	if (input[i] == '|')
		shell->last_token_type = 1;
	else if (input[i] == '>' || input[i] == '<')
		shell->last_token_type = 2;
	else
		shell->last_token_type = 0;
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
    // while ((shell->last_token_type == 1 || shell->last_token_type == 2) && **input)
    while (shell->last_token_type == 1 && **input)
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
char *ft_start_with_specials_v2(char *str) //pipe is excluded
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

    // if(shell->tokens)
    //     print_tokens(shell->tokens);

    if(!shell->tokens)
    {
        return (1);
    }
	i = 0;
	while (shell->tokens[i])
	{
		// if (ft_start_with_specials_v2(shell->tokens[i]) ||
    	// 	(strcmp(shell->tokens[i], "|") == 0 && strcmp(shell->tokens[i + 1], "|") == 0))
        if ((strcmp(shell->tokens[i], "|") == 0 && strcmp(shell->tokens[i + 1], "|") == 0))
		{
			// if (shell->tokens[i + 1] && ft_start_with_specials(shell->tokens[i + 1]) && shell->ambiguous_flag != 1) //if flag = 1 that means we dont print syntax err, but try to handle ambiguous flag for that current node
            if (shell->tokens[i + 1] && shell->ambiguous_flag != 1) //if flag = 1 that means we dont print syntax err, but try to handle ambiguous flag for that current node
			{
        		printf("minishell: syntax error.\n");
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
    
    if (ft_strcmp("", shell->input) != 0)
        parse_input_fragment(input, shell); //checking Complex scenarios with quotes, special characters, and whitespace. finally parse it to token(s)
    
    process_additional_input(shell, &input); //checking if there's un-finish quote or pipe, if yes, parse into new token(s)

    if (!shell->tokens)
    {
        //fuck2
        printf("exit code: %d\n", shell->exit_code);
        
    }

    if (empty_between_checker(shell)) //checking case like 1 | 2 | (linebreak) |    ----this is not allowed
    {
        free(input);
        shell->err_code = 258;
        clear_tokens(shell);
        return;
    }
    // shell->last_token_type = 0;
    free(input);
    
    //debug
    // printf("shell->last_token_type = %d\n", shell->last_token_type);

	// if (empty_between_checker(shell)) //checking case like 1 | 2 | (linebreak) |    ----this is not allowed
	// {
	// 	free(input);
	// 	shell->err_code = 258;
	// 	clear_tokens(shell);
	// 	return;
	// }
	// // shell->last_token_type = 0;
	// free(input);
}
