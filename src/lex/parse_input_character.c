/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_character.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:44:31 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/22 16:48:34 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void handle_consecutive_redir(t_shell *shell, char **current_token, int *i, char *input)
{
	if (input[*i + 1] != '\0' && input[*i + 1] == '>')
	{
		*current_token = str_append(shell, *current_token, input[*i]);
		*current_token = str_append(shell, *current_token, input[*i + 1]);
		(*i)++;
	}
	else
		*current_token = str_append(shell, *current_token, input[*i]);
	finalize_token(shell, current_token, &shell->token_count);
}

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
