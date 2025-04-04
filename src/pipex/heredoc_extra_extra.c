/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_extra_extra.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:42:35 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/04/04 18:59:05 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_heredoc_signal_exit(t_shell *shell, int *fds)
{
	if (set_heredoc_signal())
	{
		close_pipe_safe(fds);
		ft_free_all(shell);
		exit(1);
	}
}

int	set_minishell_signal_after_heredoc_clean(int fd)
{
	if (set_minishell_signal())
	{
		close(fd);
		return (-1);
	}
	return (0);
}
