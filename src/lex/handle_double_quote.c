/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:50:14 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/22 15:50:23 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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