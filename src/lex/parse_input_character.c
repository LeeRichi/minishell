/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_character.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:44:31 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/04 21:04:21 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_wave_helper(t_shell *shell, char **ct, int *i, char *input)
{
	char	*home_dir;
	int		j;

	home_dir = ft_getenv_value_ptr("HOME", shell);
	if (home_dir != NULL)
	{
		j = 0;
		while (home_dir[j++])
			*ct = str_append_v2(shell, *ct, home_dir[j - 1], input);
	}
	if (input[*i] == '/')
	{
		while (input[*i] != ' ' && input[*i])
		{
			*ct = str_append_v2(shell, *ct, input[*i], input);
			(*i)++;
		}
	}
}

void	handle_wave(t_shell *shell, char **current_token, int *i, char *input)
{
	if (input[*i + 1] == '|' || input[*i + 1] == '\0'
		|| input[*i + 1] == ' ' || input[*i + 1] == '/')
	{
		handle_wave_helper(shell, current_token, i, input);
		return ;
	}
	while (input[*i] == '~')
	{
		*current_token = str_append_v2(shell, *current_token, '~', input);
		(*i)++;
	}
	*current_token = str_append_v2(shell, *current_token, input[*i], input);
}

void	white_space_found_no_quote(t_shell *s, char **ct, int *i, char *input)
{
	finalize_token(s, ct, &s->token_count, input);
	if (*i < 1)
		return ;
	if (input[*i - 1] == '|')
		s->last_token_type = 1;
	else if (input[*i - 1] == '>' || input[*i - 1] == '<')
		s->last_token_type = 2;
	else
		s->last_token_type = 0;
}

void	handle_consecutive_redir(t_shell *shell, char **ct, int *i, char *input)
{
	if (input[*i + 1] != '\0' && input[*i + 1] == '>')
	{
		*ct = str_append_v2(shell, *ct, input[*i], input);
		*ct = str_append_v2(shell, *ct, input[*i + 1], input);
		(*i)++;
	}
	else if (input[*i + 1] != '\0' && input[*i] == '<' && input[*i + 1] == '<')
	{
		*ct = str_append_v2(shell, *ct, input[*i], input);
		*ct = str_append_v2(shell, *ct, input[*i + 1], input);
		(*i)++;
		shell->hd_flag++;
	}
	else
		*ct = str_append_v2(shell, *ct, input[*i], input);
	finalize_token(shell, ct, &shell->token_count, input);
}

void	parse_input_character(t_shell *shell, char **ct, int *i, char *input)
{
	if ((input[*i] == '"' && input[*i + 1] == '"')
		|| (input[*i] == '\'' && input[*i + 1] == '\''))
		handle_empty_token_strdup(shell, ct, i, input);
	else if (input[*i] == '\'' && !(shell->in_double_quote))
		handle_single_quote(shell, ct, i, input);
	else if (input[*i] == '"' && !(shell->in_single_quote))
		handle_double_quote(shell, ct, i, input);
	else if (input[*i] == '~' && !(shell->in_single_quote)
		&& !(shell->in_double_quote))
		handle_wave(shell, ct, i, input);
	else if (!(shell->in_single_quote)
		&& input[*i] == '$' && input[*i + 1] != '\0')
		massive_dollar_sign_handler(shell, ct, i, input);
	else if (strchr(WHITESPACE, input[*i]) && !(shell->in_single_quote)
		&& !(shell->in_double_quote))
		white_space_found_no_quote(shell, ct, i, input);
	else if (input[*i] == '>' || input[*i] == '<')
		handle_consecutive_redir(shell, ct, i, input);
	else
		*ct = str_append_v2(shell, *ct, input[*i], input);
}
