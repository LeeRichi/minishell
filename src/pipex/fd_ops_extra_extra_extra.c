/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_ops_extra_extra_extra.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:48:27 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/28 18:48:50 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect_fds(t_pipex *pipex)
{
	if (pipex->current_command == 0)
	{
		ft_close(&pipex->pipe[0]);
		if (dup2_and_close(&pipex->pipe[1], STDOUT_FILENO) == -1)
			error_and_exit(pipex, error_init(DUP_FAIL, 0, 0));
	}
	else if (pipex->current_command == (pipex->command_count - 1))
	{
		ft_close(&pipex->pipe[1]);
		if (pipex->current_command)
		{
			if (dup2_and_close(&pipex->reserve_fd, STDIN_FILENO) == -1)
				error_and_exit(pipex, error_init(DUP_FAIL, 0, 0));
		}
	}
	else if (process_normal_pipe(pipex) == -1)
		error_and_exit(pipex, error_init(DUP_FAIL, 0, 0));
}
