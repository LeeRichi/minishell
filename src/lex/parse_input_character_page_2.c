/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_character_page_2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:41:28 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/31 18:04:58 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_empty_token_strdup(t_shell *shell, char **ct, int *i, char *str)
{
	if (*ct == NULL)
	{
		*ct = ft_strdup("");
		if (*ct == NULL)
		{
			if (str)
				free(str);
			malloc_fail_clean_exit(shell);
		}
	}
	(*i)++;
}
