/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_fragment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:43:40 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/22 16:50:49 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// TODO: clear up and exit on malloc
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
			malloc_fail_clean_exit(shell);
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

void handle_empty_token_strdup(t_shell *shell, char **current_token,  int *i)
{	
	if (*current_token == NULL)
	{
		*current_token = ft_strdup("");
		if (*current_token == NULL)
			malloc_fail_clean_exit(shell);
	}
	(*i)++;
}

void handle_single_quote(t_shell *shell, char **current_token, int *i, char *input)
{
	shell->in_single_quote = !(shell->in_single_quote);
	(*i)++;
	while (input[*i] != '\'' && input[*i] != '\0')
	{
		*current_token = str_append(shell, *current_token, input[*i]);
		(*i)++;
	}
	if (input[*i] == '\'')
		shell->in_single_quote = !(shell->in_single_quote);
	if (ft_strcmp(*current_token, ">") == 0 || ft_strcmp(*current_token, ">>") == 0 || ft_strcmp(*current_token, "<") == 0)
		shell->has_quotes++;
}

void handle_dollar_question_in_double_quote(t_shell *shell, char **current_token, int *i)
{
	char *itoaed_str;
	int j;

	itoaed_str = ft_itoa(shell->exit_code);
	if (!itoaed_str)
		malloc_fail_clean_exit(shell);
	j = 0;
	while(itoaed_str[j])
	{
		*current_token = str_append(shell, *current_token, itoaed_str[j]);
		j++;
	}
	free(itoaed_str);
	(*i)++;
}

void handle_dollar_in_double_quote(t_shell *shell, char **current_token, int *i, char *input)
{
	char *env_value;
	int j;
	
	if (input[*i + 1] == '?')
		handle_dollar_question_in_double_quote(shell, current_token, i);
	else
	{
		env_value = handle_dollar_sign(shell, input, i);
		if (!env_value)
			*current_token = str_append(shell, *current_token, input[*i]);
		else
		{
			j = 0;
			while (env_value[j])
				*current_token = str_append(shell, *current_token, env_value[j++]);
			free(env_value);
		}
	}
}

void handle_double_quote(t_shell *shell, char **current_token, int *i, char *input)
{
	shell->in_double_quote = !(shell->in_double_quote);
	(*i)++;
	while (input[*i] != '"' && input[*i] != '\0')
	{
		if (strchr("$", input[*i]))
			handle_dollar_in_double_quote(shell, current_token, i, input);
		else
			*current_token = str_append(shell, *current_token, input[*i]);
		(*i)++;
	}
	if (input[*i] == '"')
		shell->in_double_quote = !(shell->in_double_quote);
	if (ft_strcmp(*current_token, ">") == 0 || ft_strcmp(*current_token, ">>") == 0 || ft_strcmp(*current_token, "<") == 0)
		shell->has_quotes++;
}

void handle_wave(t_shell *shell, char **current_token, int *i, char *input)
{
	int j;

	if (input[*i + 1] == '|' || input[*i + 1] == '\0' || input[*i + 1] == ' ' || input[*i + 1] == '/')
	{
		char *home_dir = ft_getenv("HOME", shell);
		if (home_dir != NULL)
		{
			j = 0;
			while (home_dir[j++])
				*current_token = str_append(shell, *current_token, home_dir[j-1]);
			free(home_dir);
		}
		if (input[*i] == '/')
		{
			while (input[*i] != ' ' && input[*i])
			{
				*current_token = str_append(shell, *current_token, input[*i]);
				(*i)++;
			}
		}
		return ;
	}
	while (input[*i] == '~')
	{
		*current_token = str_append(shell, *current_token, '~');
		(*i)++;
	}
	*current_token = str_append(shell, *current_token, input[*i]);
}

void handle_consecutive_dollar(t_shell *shell, char **current_token, int *i, char *input)
{
	char *id_as_str;
	int str_len;
	int j;

	id_as_str = ft_itoa(shell->shell_id);
	if (!id_as_str)
		malloc_fail_clean_exit(shell);
	str_len = ft_strlen(id_as_str);
	j = 0;
	while(j < str_len)
	{
		*current_token = str_append(shell, *current_token, id_as_str[j]);
		j++;
	}
	free(id_as_str);
	(*i) += 2;
	while(input[*i] == '$')
	{
		*current_token = str_append(shell, *current_token, '$');
		(*i)++;
	}
}

void handle_dollar_question(t_shell *shell, char **current_token, int *i)
{
	char *itoaed_str;
	int j = 0;

	itoaed_str = ft_itoa(shell->exit_code);
	if (!itoaed_str)
		malloc_fail_clean_exit(shell);
	j = 0;
	while(itoaed_str[j])
	{
		*current_token = str_append(shell, *current_token, itoaed_str[j]);
		j++;
	}
	free(itoaed_str);
	(*i)++;
}

void massive_dollar_sign_handler_helper(t_shell *shell, char **current_token, int *i, char *input)
{
	char *env_value;
	int j;
	
	env_value = handle_dollar_sign(shell, input, i);
	if (!env_value)
		return ;
	else
	{
		j = 0;
		while (env_value[j])
			*current_token = str_append(shell, *current_token, env_value[j++]);
		free(env_value);
	}
}

void massive_dollar_sign_handler(t_shell *shell, char **current_token, int *i, char *input)
{
	if (strchr("$", input[*i + 1]) && input[*i + 1] != '\0')
		handle_consecutive_dollar(shell, current_token, i, input);
	else if (strchr("?", input[*i + 1]))
		handle_dollar_question(shell, current_token, i);
	else if ((strchr("\'", input[*i + 1]) && shell->in_single_quote) || (strchr("\"", input[*i + 1]) && shell->in_double_quote))
	{
		*current_token = str_append(shell, *current_token, '$');
		return ;
	}
	else if (strchr(" ", input[*i + 1]))
		*current_token = str_append(shell, *current_token, '$');
	else
		massive_dollar_sign_handler_helper(shell, current_token, i, input);
}

void white_space_found_without_quote(t_shell *shell, char **current_token, int *i, char *input)
{
	finalize_token(shell, current_token, &shell->token_count);
	if (input[*i - 1] == '|')
		shell->last_token_type = 1;
	else if (input[*i - 1] == '>' || input[*i - 1] == '<')
		shell->last_token_type = 2;
	else
		shell->last_token_type = 0;
}

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
void parse_input_character(t_shell *shell, char **current_token, int *i, char *input)
{
    if ((input[*i] == '"' && input[*i + 1] == '"') || (input[*i] == '\'' && input[*i + 1] == '\''))
    	handle_empty_token_strdup(shell, current_token, i);
	else if (input[*i] == '\'' && !(shell->in_double_quote))
		handle_single_quote(shell, current_token, i, input);
    else if (input[*i] == '"' && !(shell->in_single_quote))
		handle_double_quote(shell, current_token, i, input);
    else if (input[*i] == '~' && !(shell->in_single_quote) && !(shell->in_double_quote))
		handle_wave(shell, current_token, i, input);
    else if (!(shell->in_single_quote) && input[*i] == '$' && input[*i + 1] != '\0')
		massive_dollar_sign_handler(shell, current_token, i, input);
    else if (strchr(WHITESPACE, input[*i]) && !(shell->in_single_quote) && !(shell->in_double_quote))
		white_space_found_without_quote(shell, current_token, i, input);
    else if (input[*i] == '>' || input[*i] == '<')
		handle_consecutive_redir(shell, current_token, i, input);
    else
        *current_token = str_append(shell, *current_token, input[*i]);
}

void parse_input_fragment(char *input, t_shell *shell)
{
    char *current_token;
    int i;
	
	i = 0;
	current_token = NULL;
	if (shell->tokens)
		shell->token_count = count_split(shell->tokens);
	else
		shell->token_count = 0;
    while (input[i] != '\0')
    {
        parse_input_character(shell, &current_token, &i, input);
        i++;
    }
    finalize_token(shell, &current_token, &shell->token_count);
	while(ft_strchr(WHITESPACE, input[i]))
		i--;
	if (input[i] == '|')
		shell->last_token_type = 1;
	else if (input[i] == '>' || input[i] == '<')
		shell->last_token_type = 2;
	else
		shell->last_token_type = 0;
}
