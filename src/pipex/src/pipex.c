/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 23:22:51 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/12/10 14:07:47 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	pid_t	pid;
	int		wait_all_return;

	if (argc != 5)
	{
		ft_putendl_fd("Provide 4 arguments", 2);
		return (EXIT_FAILURE);
	}
	pipex = get_pipex(argc, argv, env);
	while (pipex.current_command < pipex.command_count)
	{
		before_fork(&pipex);
		pid = fork();
		if (pid != -1)
			pipex.last_pid = pid;
		after_fork(pid, &pipex);
		pipex.current_command++;
	}
	ft_close(&pipex.pipe[0]);
	ft_close(&pipex.pipe[1]);
	wait_all_return = wait_all(pipex);
	free_all(pipex);
	return (wait_all_return);
}
