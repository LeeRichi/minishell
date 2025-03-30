/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:50:14 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/30 19:00:17 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	hd_question_in_double_quote(t_shell *shell, char **ct, int *i, char *s)
{
	char	*itoaed_str;
	int		j;

	itoaed_str = ft_itoa(shell->exit_code);
	if (!itoaed_str)
	{
		if (s)
			free(s);
		malloc_fail_clean_exit(shell);
	}
	j = 0;
	while (itoaed_str[j])
	{
		*ct = str_append_v2(shell, *ct, itoaed_str[j], itoaed_str);
		j++;
	}
	free(itoaed_str);
	(*i)++;
}

void	hd_in_double_quote(t_shell *shell, char **ct, int *i, char *s)
{
	char	*env_value;
	int		j;

	if (s[*i + 1] == '?')
		hd_question_in_double_quote(shell, ct, i, s);
	else
	{
		env_value = handle_dollar_sign(shell, s, i);
		if (!env_value)
			*ct = str_append(shell, *ct, s[*i]);
		else
		{
			j = 0;
			while (env_value[j])
				*ct = str_append(shell, *ct, env_value[j++]);
			// free(env_value);
		}
	}
}

void	handle_double_quote(t_shell *shell, char **ct, int *i, char *input)
{
	shell->in_double_quote = !(shell->in_double_quote);
	(*i)++;
	while (input[*i] != '"' && input[*i] != '\0')
	{
		if (ft_strchr("$", input[*i]))
			hd_in_double_quote(shell, ct, i, input);
		else
			*ct = str_append_v2(shell, *ct, input[*i], input);
		(*i)++;
	}
	if (input[*i] == '"')
		shell->in_double_quote = !(shell->in_double_quote);
	if (ft_strcmp(*ct, ">") == 0 || ft_strcmp(*ct, ">>") == 0
		|| ft_strcmp(*ct, "<") == 0)
		shell->has_quotes++;
}
