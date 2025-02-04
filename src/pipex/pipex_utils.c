/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:31:10 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/02/04 19:59:35 by mbutuzov         ###   ########.fr       */
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

t_pipex_command cmd_to_pipex_command(t_cmd cmd, char **envp)
{
	t_pipex_command	command;
// happens in child
	command.env = envp;
	command.infiles = cmd.infiles;
	command.outfiles = cmd.outfiles;
	command.type = cmd.type;
//fill in child?
	command.path = 0;
	command.argv = 0;
// TODO: ??
	command.input_arg = 0;
	return (command);
}

/* TODO: keep in mind order of freeing */

t_cmd *cmd_list_to_arr(t_cmd *cmds, size_t command_count)
{
	t_cmd	*arr;
	size_t i;

	i = 0;
	arr = malloc((command_count + 1) * sizeof(t_cmd));
	if (!arr)
		return (0);
	ft_bzero(&arr[command_count], sizeof(t_cmd));
	while(i < command_count)
	{
		arr[i] = *cmds;
		cmds = cmds.next;
		i++;
	}
	return (arr);
}

t_pipex	get_pipex(size_t command_count, t_cmd *commands, char **envp)
{
	t_pipex	pipex;

	pipex.command_count = command_count;
	pipex.current_command = 0;
// TODO : rethink where to do this
/*
	pipex.infile = *(argv + 1);
	pipex.outfile = *(argv + (argc - 1));
*/
//	pipex.first_command = (argv + 2);
	//pipex.first_command = commands;
	pipex.env = envp;
	pipex.last_pid = -1;
	pipex.reserve_fd = -1;
	pipex.pipe[0] = -1;
	pipex.pipe[1] = -1;
//TODO: null check
	pipex.command = cmd_list_to_arr(commands, char **envp);
//TODO: free list
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
