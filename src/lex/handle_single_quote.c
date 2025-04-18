/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:48:00 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/12 22:22:42 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_single_quote(t_shell *shell, char **ct, int *i, char *input)
{
	shell->expanded_ct_flag = 1;
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
		return ;
	else
		return ;
}
