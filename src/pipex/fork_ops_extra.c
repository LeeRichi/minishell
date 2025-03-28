/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_ops_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:38:00 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/28 18:38:29 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_exit_code(int wstatus)
{
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else if (WIFSIGNALED(wstatus))
		return (128 + WTERMSIG(wstatus));
	return (1);
}

int	wait_all(t_pipex pipex)
{
	int	wstatus;
	int	exit_status;
	int	sig_int_child;
	int	wait_res;

	sig_int_child = 0;
	wstatus = 0;
	exit_status = EXIT_FAILURE;
	while (pipex.current_command--)
	{
		wait_res = wait(&wstatus);
		if (wait_res == -1)
			break ;
		if (wait_res == pipex.last_pid)
		{
			exit_status = get_exit_code(wstatus);
			if (exit_status == 130 && !sig_int_child++)
				ft_putstr_fd("\n", 2);
			if (exit_status == 131)
				ft_putstr_fd("Quit (Core dumped)\n", 2);
		}
		else if (get_exit_code(wstatus) == 130 && !sig_int_child++)
			ft_putstr_fd("\n", 2);
	}
	return (exit_status);
}
