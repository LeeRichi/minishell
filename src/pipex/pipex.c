/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 23:22:51 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/02/04 16:49:07 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
TODO: set

adapt to t_cmd:
	remove some pieces from t_pipex, as they already exist in t_cmd
	
	rewrite get pipex:
	


*/
/*
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
*/
int	pipex_launch(int command_count, char **argv, char **env)
{
	t_pipex	pipex;
	pid_t	pid;
	int		wait_all_return;
	if (command_count < 1)
	{
// TODO: rethink this logic, find out about return logic and general exit code logic
		ft_putendl_fd("Provide 4 arguments", 2);
//		return (EXIT_FAILURE);
		return (0)
	}
	pipex = get_pipex(command_count, argv, env);
// different logic if command count == 1 and builtin is used (no fork)
	while (pipex.current_command < pipex.command_count)
	{
		//TODO: change logic of error and exit in before fork, as you should not exit from minishell, or should you?
		before_fork(&pipex);
		pid = fork();
		if (pid != -1)
			pipex.last_pid = pid;
		//TODO: change logic of error and exit in after fork, as you should not exit from minishell, or should you?
		after_fork(pid, &pipex);
		pipex.current_command++;
	}
	ft_close(&pipex.pipe[0]);
	ft_close(&pipex.pipe[1]);
// TODO: wait fails considiration?
	wait_all_return = wait_all(pipex);
//TODO:  adjust free_all
	free_all(pipex);
	return (wait_all_return);
}
