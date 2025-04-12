/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_tokens_helper_p2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:12:58 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/12 22:18:19 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	yeah_found_the_tricky_cmd(t_shell *shell, int i, int j)
{
	return (
		shell->tokens[i] && shell->expanded_tokens_arr[j]
		&& shell->tokens[i] == shell->expanded_tokens_arr[j]
	);
}

void	loop_tokens(t_shell *shell, t_cmd *current_cmd)
{
	int		i;
	t_cmd	*new_cmd;
	int		handled;

	new_cmd = NULL;
	i = 0;
	while (shell->tokens[i])
	{
		if (make_new_node(shell, &current_cmd, &i))
			break ;
		handled = compare_each_from_two_arr_and_do(shell, current_cmd, &i);
		if (handled)
			continue ;
		if (is_one_of_redir(shell, i))
			struct_redir(shell, current_cmd, &i);
		else
			struct_else(shell, current_cmd, &i);
		i++;
	}
}
