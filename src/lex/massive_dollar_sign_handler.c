/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   massive_dollar_sign_handler.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:45:55 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/25 16:45:42 by chlee2           ###   ########.fr       */
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

//last_token_index == z
void	handler_helper(t_shell *shell, char **ct, int *i, char *input)
{
	char	*env_value;
	int		j;
	int		z;

	env_value = handle_dollar_sign(shell, input, i);
	if (!env_value)
	{
		z = 0;
		if (!shell->tokens)
			return ;
		while (shell->tokens[z])
			z++;
		if (!z)
			return ;
		if (ft_start_with_specials(shell->tokens[z - 1]))
			*ct = str_append(shell, *ct, '\0');
		return ;
	}
	else
	{
		j = 0;
		while (env_value[j])
			*ct = str_append(shell, *ct, env_value[j++]);
		free(env_value);
	}
}

void	do_not_expand(t_shell *shell, char **ct, int *i, char *input)
{
	while (input[*i] != ' ' && input[*i])
	{
		*ct = str_append(shell, *ct, input[*i]);
		(*i)++;
	}
	(*i)--;
	shell->hd_flag--;
}

void	massive_dollar_sign_handler(t_shell *shell, char **ct, int *i, char *s)
{
	if (ft_strchr("$", s[*i + 1]) && s[*i + 1] != '\0')
		handle_consecutive_dollar(shell, ct, i, s);
	else if (ft_strchr("?", s[*i + 1]))
		handle_dollar_question(shell, ct, i);
	else if ((ft_strchr("\'", s[*i + 1]) && shell->in_single_quote)
		|| (ft_strchr("\"", s[*i + 1]) && shell->in_double_quote))
	{
		*ct = str_append(shell, *ct, '$');
		return ;
	}
	else if (ft_strchr(" ", s[*i + 1]))
		*ct = str_append(shell, *ct, '$');
	else if (shell->hd_flag)
		do_not_expand(shell, ct, i, s);
	else
		handler_helper(shell, ct, i, s);
}
