/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:10:48 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/10 18:03:07 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse(t_shell *shell)
{
	tokenize_input(shell->input, shell);
	
	if (shell->tokens)
		print_tokens(shell->tokens);
	else
		printf("tokens are 0 at parse, before struct\n");
	if (!shell->err_code && shell->tokens)
		ft_structlize(shell);

	print_cmd_struct(shell->cmds);
	// shell->err_code = 0;
	// shell->ambiguous_flag = 0;
	

	
	// shell->has_quotes = 0;


	
	
	
	
	
	
	shell->hd_flag = 0;


	
    shell->err_code = 0;
    shell->ambiguous_flag = 0;
}
