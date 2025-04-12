/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_tokens_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:08:31 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/12 22:16:36 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	loop_tokens_helper(t_shell *shell, int *i, t_cmd *current_cmd)
{
	int	handled;
	int	j;

	j = 0;
	handled = 0;
	while (shell->expanded_tokens_arr && shell->expanded_tokens_arr[j])
	{
		if (shell->tokens[*i] && shell->expanded_tokens_arr[j]
			&& shell->tokens[*i] == shell->expanded_tokens_arr[j])
		{
			struct_else(shell, current_cmd, i);
			handled = 1;
			i++;
			break ;
		}
		j++;
	}
	return (handled);
}

int	ok_now_make_nodes(t_shell *shell, t_cmd *current_cmd, int i)
{
	return (
		current_cmd == NULL || (!is_array_member(shell->tokens[i]
				, shell->expanded_tokens_arr)
			&& ft_strcmp(shell->tokens[i], "|") == 0)
	);
}

int	is_one_of_redir(t_shell *shell, int i)
{
	return (
		shell->tokens[i] && (ft_strcmp(shell->tokens[i], "<<") == 0
			|| ft_strcmp(shell->tokens[i], ">>") == 0
			|| ft_strcmp(shell->tokens[i], ">") == 0
			|| ft_strcmp(shell->tokens[i], "<") == 0)
	);
}

int	compare_each_from_two_arr_and_do(t_shell *shell, t_cmd *current_cmd, int *i)
{
	int	handled;
	int	j;

	handled = 0;
	j = 0;
	while (shell->expanded_tokens_arr && shell->expanded_tokens_arr[j])
	{
		if (yeah_found_the_tricky_cmd(shell, *i, j))
		{
			struct_else(shell, current_cmd, i);
			handled = 1;
			(*i)++;
			break ;
		}
		j++;
	}
	return (handled);
}

int	make_new_node(t_shell *shell, t_cmd **current_cmd, int *i)
{
	t_cmd	*new_cmd;

	new_cmd = NULL;
	if (ok_now_make_nodes(shell, *current_cmd, *i))
	{
		allocate_nodes(current_cmd, &new_cmd, shell);
		if (ft_strcmp(shell->tokens[*i], "|") == 0)
		{
			(*i)++;
			if (!shell->tokens[*i])
				return (1);
		}
	}
	return (0);
}
