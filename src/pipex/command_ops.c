/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:23:25 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/25 15:32:54 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "pipex.h"
//#include "minishell.h"
#include "../../includes/minishell.h"
/*
static void err_and_exit(char *fname, int line, t_pipex *pipex, t_error error)
{
	printf("%s, %d", fname, line);
	error_and_exit(pipex, error);
}
#define error_and_exit(x, y) err_and_exit(__FILE__, __LINE__, x, y)
*/
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
/*
static char	**get_alt_argv(char *input_arg)
{
	char	**new_argv;

	new_argv = malloc(2 * sizeof(char *));
	if (!new_argv)
		return (NULL);
	new_argv[0] = ft_strdup(input_arg);
	new_argv[1] = 0;
	if (!new_argv[0])
	{
		free(new_argv);
		return (NULL);
	}
	return (new_argv);
}
*/

static void	handle_command(char **path_split, t_pipex *pipex)
{
	char	*command_tmp;

	command_tmp = ft_strjoin("/", pipex->command[pipex->current_command].argv[0]);
	if (!command_tmp)
		error_and_exit(pipex, error_init(MALLOC_FAIL, 0, 0));
	pipex->command[pipex->current_command].path = get_command_path(command_tmp, path_split);
	free(command_tmp);
	if (!pipex->command[pipex->current_command].path && errno == ENOMEM)
		error_and_exit(pipex, error_init(MALLOC_FAIL, 0, 0));
	else if (!pipex->command[pipex->current_command].path)
		error_and_exit(pipex, error_init(CMD_NOT_FOUND, 0, pipex->command[pipex->current_command].cmd_name));
}

static void	resolve_command_path(t_pipex *pipex)
{
	ssize_t	ind;

	if (pipex->command[pipex->current_command].argv[0] == 0)
	{
		pipex->command[pipex->current_command].path = 0;
		pipex->command[pipex->current_command].argv = 0;
			error_and_exit(pipex, error_init(PROG_FILE_IS_DIR, 0, pipex->command[pipex->current_command].cmd_name));
	}
	if (ft_strchr(pipex->command[pipex->current_command].argv[0], '/'))
	{
		pipex->command[pipex->current_command].path = pipex->command[pipex->current_command].argv[0];
		if (!check_exists_and_not_dir(pipex->command[pipex->current_command].path) && !errno)
			error_and_exit(pipex, error_init(PROG_FILE_IS_DIR, 0, pipex->command[pipex->current_command].cmd_name));
	}
	else
	{
		ind = get_path_index(pipex->env);
		if (ind == -1)
		{
			pipex->command[pipex->current_command].path = pipex->command[pipex->current_command].argv[0];
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
	pipex->command[pipex->current_command].argv = get_command_argv(pipex->command[pipex->current_command]);
	if (!pipex->command[pipex->current_command].argv)
		error_and_exit(pipex, error_init(MALLOC_FAIL, 0, 0));
	resolve_command_path(pipex);
	pipex->command[pipex->current_command].env = pipex->env;
}
