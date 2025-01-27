/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:31:10 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/12/09 15:04:37 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_command_argv(char *arg)
{
	return (ft_split(arg, ' '));
}

char	**get_path_split(char **envp, size_t ind)
{
	envp[ind] += 5;
	return (ft_split(envp[ind], ':'));
}

t_pipex	get_pipex(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.command_count = ((size_t)argc - 3);
	pipex.current_command = 0;
	pipex.infile = *(argv + 1);
	pipex.outfile = *(argv + (argc - 1));
	pipex.first_command = (argv + 2);
	pipex.env = envp;
	pipex.last_pid = -1;
	pipex.reserve_fd = -1;
	pipex.pipe[0] = -1;
	pipex.pipe[1] = -1;
	pipex.command = 0;
	pipex.path_split = 0;
	return (pipex);
}

t_command	*free_command_content(t_command *command)
{
	if (command)
	{
		if (command->argv)
		{
			if (command->path && command->argv[0] == command->path)
				command->path = 0;
			free_split(command->argv);
			command->argv = 0;
		}
		if (command->path)
		{
			free(command->path);
			command->path = 0;
		}
	}
	return (0);
}

void	free_all(t_pipex pipex)
{
	if (pipex.command)
		free_command_content(pipex.command);
	if (pipex.path_split)
		free_split(pipex.path_split);
	ft_close(&pipex.pipe[0]);
	ft_close(&pipex.pipe[1]);
	ft_close(&pipex.reserve_fd);
}
