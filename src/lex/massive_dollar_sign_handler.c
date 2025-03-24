/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   massive_dollar_sign_handler.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:45:55 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/24 21:20:40 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_consecutive_dollar(t_shell *shell, char **ct, int *i, char *s)
{
	char	*id_as_str;
	int		str_len;
	int		j;

	id_as_str = ft_itoa(shell->shell_id);
	if (!id_as_str)
		malloc_fail_clean_exit(shell);
	str_len = ft_strlen(id_as_str);
	j = 0;
	while (j < str_len)
	{
		*ct = str_append(shell, *ct, id_as_str[j]);
		j++;
	}
	free(id_as_str);
	(*i) += 2;
	while (s[*i] == '$')
	{
		*ct = str_append(shell, *ct, '$');
		(*i)++;
	}
}

void	handle_dollar_question(t_shell *shell, char **current_token, int *i)
{
	char	*itoaed_str;
	int		j;

	j = 0;
	itoaed_str = ft_itoa(shell->exit_code);
	if (!itoaed_str)
		malloc_fail_clean_exit(shell);
	j = 0;
	while (itoaed_str[j])
	{
		*current_token = str_append(shell, *current_token, itoaed_str[j]);
		j++;
	}
	free(itoaed_str);
	(*i)++;
}

void	handler_helper(t_shell *shell, char **ct, int *i, char *input)
{
	char	*env_value;
	int		j;

	env_value = handle_dollar_sign(shell, input, i);
	if (!env_value)
		return ;
	else
	{
		j = 0;
		while (env_value[j])
			*ct = str_append(shell, *ct, env_value[j++]);
		free(env_value);
	}
}

void	massive_dollar_sign_handler(t_shell *shell, char **ct, int *i, char *s)
{
	if (strchr("$", s[*i + 1]) && s[*i + 1] != '\0')
		handle_consecutive_dollar(shell, ct, i, s);
	else if (strchr("?", s[*i + 1]))
		handle_dollar_question(shell, ct, i);
	else if ((strchr("\'", s[*i + 1]) && shell->in_single_quote)
		|| (strchr("\"", s[*i + 1]) && shell->in_double_quote))
	{
		*ct = str_append(shell, *ct, '$');
		return ;
	}
	else if (strchr(" ", s[*i + 1]))
		*ct = str_append(shell, *ct, '$');
	else
		handler_helper(shell, ct, i, s);
}
