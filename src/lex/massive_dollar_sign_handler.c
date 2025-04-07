/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   massive_dollar_sign_handler.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:45:55 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/07 18:53:06 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_dollar_question(t_shell *shell, char **ct, int *i, char *s)
{
	int				j;
	t_free_struc	temp;

	ft_bzero(&temp, sizeof(t_free_struc));
	temp.input = s;
	j = 0;
	temp.itoaed_str = ft_itoa(shell->exit_code);
	if (!temp.itoaed_str)
	{
		if (*ct)
			free(*ct);
		if (s)
			free(s);
		malloc_fail_clean_exit(shell);
	}
	j = 0;
	while (temp.itoaed_str[j])
	{
		*ct = str_append_v3(shell, *ct, temp.itoaed_str[j], &temp);
		j++;
	}
	free(temp.itoaed_str);
	(*i)++;
}

void	handler_helper(t_shell *shell, char **ct, int *i, char *input)
{
	char	*env_value;
	int		j;

	env_value = handle_dollar_sign(shell, input, i, *ct);
	if (!env_value)
	{
		if (input[*i] == '$' && input[*i] == '\0')
			*ct = str_append_v2(shell, *ct, input[*i], input);
		else
			*ct = str_append_v2(shell, *ct, 0, input);
	}
	else
	{
		j = 0;
		while (env_value[j])
			*ct = str_append_v2(shell, *ct, env_value[j++], input);
	}
}

void	do_not_expand(t_shell *shell, char **ct, int *i, char *input)
{
	while (input[*i] != ' ' && input[*i]
		&& input[*i] != '"' && input[*i] != '\'')
	{
		*ct = str_append_v2(shell, *ct, input[*i], input);
		(*i)++;
	}
	(*i)--;
	if (*i < 0)
		*i = 0;
	shell->hd_flag--;
}

void	massive_dollar_sign_handler(t_shell *shell, char **ct, int *i, char *s)
{
	if (ft_strchr("?", s[*i + 1]))
		handle_dollar_question(shell, ct, i, s);
	else if ((ft_strchr("\'", s[*i + 1]) && shell->in_single_quote)
		|| (ft_strchr("\"", s[*i + 1]) && shell->in_double_quote))
	{
		*ct = str_append_v2(shell, *ct, '$', s);
		return ;
	}
	else if (ft_strchr(" ", s[*i + 1]))
		*ct = str_append_v2(shell, *ct, '$', s);
	else if (shell->hd_flag)
		do_not_expand(shell, ct, i, s);
	else
		handler_helper(shell, ct, i, s);
}
