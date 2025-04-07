/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:48:00 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/07 16:36:56 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_single_quote(t_shell *shell, char **ct, int *i, char *input)
{
	shell->in_single_quote = !(shell->in_single_quote);
	(*i)++;
	while (input[*i] != '\'' && input[*i] != '\0')
	{
		*ct = str_append_v2(shell, *ct, input[*i], input);
		(*i)++;
	}
	if (input[*i] == '\'')
		shell->in_single_quote = !(shell->in_single_quote);
	if (ft_strchr(input, '"') || ft_strchr(input, '\''))
	{
		shell->has_quotes++;
		return ;
	}
	if (ft_strcmp(*ct, ">") == 0 || ft_strcmp(*ct, ">>") == 0
		|| ft_strcmp(*ct, "<") == 0)
		shell->has_quotes++;
	else
		return ;
}
