/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:23:27 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/04/02 20:13:00 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_pipex	get_pipex(size_t command_count, t_cmd *commands,
	char **envp, t_shell *shell)
{
	t_pipex	pipex;

	pipex.command_count = command_count;
	pipex.current_command = 0;
	pipex.shell = (void *)shell;
	pipex.env = envp;
	pipex.last_pid = -1;
	pipex.reserve_fd = -1;
	pipex.pipe[0] = -1;
	pipex.pipe[1] = -1;
	pipex.command = cmd_list_to_arr(commands, command_count, shell);
	pipex.path_split = 0;
	return (pipex);
}

t_cmd	*free_pipex_cmd(t_cmd *command)
{
	while (command->cmd_name || command->infiles || command->outfiles)
	{
		if (command->argv)
		{
			free(command->argv);
			command->argv = 0;
		}
		if (command->path && command->path != command->cmd_name)
		{
			free(command->path);
			command->path = 0;
		}
		if (command->heredoc_fd != -1)
		{
			close(command->heredoc_fd);
			command->heredoc_fd = -1;
		}
		command++;
	}
	return (0);
}

void	free_pipex(t_pipex pipex)
{
//	static int counter;
//	counter++;
	if (pipex.command)
	{
		free_pipex_cmd(pipex.command);
		free(pipex.command);
		pipex.command = 0;
	}
	if (pipex.path_split)
		free_split(pipex.path_split);
//	printf("errno: %d\ncounter: %d\n", errno, counter);
	printf("errno before close attempt: %d\n", errno);
	printf("pipe 0 before ft_close: %d\n", pipex.pipe[0]);
	if (pipex.pipe[0] == pipex.reserve_fd)
		pipex.reserve_fd = -1;
	ft_close(&pipex.pipe[0]);
	printf("errno: %d\n", errno);
	printf("pipe 1 before ft_close: %d\n", pipex.pipe[1]);
	ft_close(&pipex.pipe[1]);
	printf("errno: %d\n", errno);
	printf("reserve_fd before ft_close: %d\n", pipex.reserve_fd);
	ft_close(&pipex.reserve_fd);
	printf("errno: %d\n", errno);
}
