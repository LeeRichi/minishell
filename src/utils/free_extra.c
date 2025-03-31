/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:04:57 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/31 22:16:54 by chlee2           ###   ########.fr       */
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

void	malloc_fail_clean_exit_v2(t_shell *shell, char *free_me)
{
	if (free_me)
		free(free_me);
	malloc_fail_clean_exit(shell);
}

void	malloc_fail_clean_exit_v3(t_shell *shell, char *free_me, char *fm2)
{
	if (fm2)
		free(fm2);
	malloc_fail_clean_exit_v2(shell, free_me);
}
