/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:50:14 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/04 20:35:50 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	hd_question_in_double_quote(t_shell *shell, char **ct, int *i, char *s)
{
	char	*itoaed_str;
	int		j;
	char	*to_free[3];

	itoaed_str = ft_itoa(shell->exit_code);
	to_free[0] = itoaed_str;
	to_free[1] = s;
	to_free[2] = 0;
	if (!itoaed_str)
	{
		if (s)
			free(s);
		malloc_fail_clean_exit(shell);
	}
	j = 0;
	while (itoaed_str[j])
	{
		*ct = str_append_v4(shell, *ct, itoaed_str[j], to_free);
		j++;
	}
	free(itoaed_str);
	(*i)++;
}

static void	hd_in_double_quote_helper(t_shell *shell,
	char **ct, int *i, char *s)
{
	int		j;
	char	*env_value;

	env_value = handle_dollar_sign(shell, s, i, *ct);
	if (!env_value)
	{	
		if (s[*i] == '$')
			*ct = str_append_v2(shell, *ct, s[*i], s);
		else
			*ct = str_append_v2(shell, *ct, 0, s);
	}
	else
	{
		j = 0;
		while (env_value[j])
			*ct = str_append_v2(shell, *ct, env_value[j++], s);
	}
}

void	hd_in_double_quote(t_shell *shell, char **ct, int *i, char *s)
{
	if (s[*i + 1] == '?')
		hd_question_in_double_quote(shell, ct, i, s);
	else
	{
		if (shell->hd_flag)
			do_not_expand(shell, ct, i, s);
		else
			hd_in_double_quote_helper(shell, ct, i, s);
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
	if (*ct && (ft_strcmp(*ct, ">") == 0 || ft_strcmp(*ct, ">>") == 0
		|| ft_strcmp(*ct, "<") == 0))
		shell->has_quotes++;
}
