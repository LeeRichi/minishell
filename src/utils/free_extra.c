/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:04:57 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/28 19:05:25 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_cmds(t_shell *shell)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!shell || !shell->cmds)
		return ;
	current = shell->cmds;
	while (current)
	{
		next = current->next;
		ft_free_parsed_cmd(current);
		current = next;
	}
	shell->cmds = NULL;
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	malloc_fail_clean_exit(t_shell *shell)
{
	ft_printf_fd(STDERR, "malloc fail\n");
	ft_free_all(shell);
	exit(EXIT_FAILURE);
}

void	free_key_value_list(t_key_value *head)
{
	t_key_value	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

