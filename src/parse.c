/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:10:48 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/04 18:20:39 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse(t_shell *shell)
{
	tokenize_input(shell->input, shell);
	if (!shell->err_code && shell->tokens)
		ft_structlize(shell);
	shell->err_code = 0;
	shell->ambiguous_flag = 0;
}
