/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:23:25 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/25 16:54:33 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static ssize_t	get_path_index(char **envp)
{
	ssize_t	i;
	int		ptr;

	i = 0;
	while (envp[i])
	{
		ptr = ft_strncmp(envp[i], "PATH=", 5);
		if (ptr == 0 && envp[i][5] != 0)
			return ((size_t)i);
		i++;
	}
	return (-1);
}

static void	handle_command(char **path_split, t_pipex *pipex)
{
	char	*command_tmp;
	t_cmd	*command;

	command = &pipex->command[pipex->current_command];
	command_tmp = ft_strjoin("/", command->argv[0]);
	if (!command_tmp)
		error_and_exit(pipex, error_init(MALLOC_FAIL, 0, 0));
	command->path = get_command_path(command_tmp, path_split);
	free(command_tmp);
	if (!command->path && errno == ENOMEM)
		error_and_exit(pipex, error_init(MALLOC_FAIL, 0, 0));
	else if (!command->path)
		error_and_exit(pipex, error_init(CMD_NOT_FOUND, 0, command->cmd_name));
}

static void	check_command_path_is_dir(t_pipex *pipex, t_cmd *command)
{
	if (command->argv[0] == 0)
	{
		command->path = 0;
		command->argv = 0;
		error_and_exit(pipex, error_init(PROG_FILE_IS_DIR,
				0, command->cmd_name));
	}
}

static void	resolve_command_path(t_pipex *pipex)
{
	ssize_t	ind;
	t_cmd	*command;

	command = &pipex->command[pipex->current_command];
	check_command_path_is_dir(pipex, command);
	if (ft_strchr(command->argv[0], '/'))
	{
		command->path = command->argv[0];
		if (!check_exists_and_not_dir(command->path) && !errno)
			error_and_exit(pipex, error_init(PROG_FILE_IS_DIR,
					0, command->cmd_name));
	}
	else
	{
		ind = get_path_index(pipex->env);
		if (ind == -1)
		{
			command->path = command->argv[0];
			return ;
		}
		pipex->path_split = get_path_split(pipex->env, (size_t)ind);
		if (!pipex->path_split)
			error_and_exit(pipex, error_init(MALLOC_FAIL, 0, 0));
		handle_command(pipex->path_split, pipex);
	}
}

void	get_command(t_pipex *pipex)
{
	t_cmd	*command;

	command = &pipex->command[pipex->current_command];
	command->argv = get_command_argv(*command);
	if (!command->argv)
		error_and_exit(pipex, error_init(MALLOC_FAIL, 0, 0));
	resolve_command_path(pipex);
	command->env = pipex->env;
}
