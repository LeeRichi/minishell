/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:23:25 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/02/05 21:35:36 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "pipex.h"
//#include "minishell.h"
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

	command_tmp = ft_strjoin("/", pipex->command->argv[0]);
	if (!command_tmp)
		error_and_exit(pipex, MALLOC_FAIL);
	pipex->command->path = get_command_path(command_tmp, path_split);
	free(command_tmp);
	if (!pipex->command->path && errno == ENOMEM)
		error_and_exit(pipex, MALLOC_FAIL);
	else if (!pipex->command->path)
		error_and_exit(pipex, CMD_NOT_FOUND);
}

static void	resolve_command_path(t_pipex *pipex)
{
	ssize_t	ind;

	if (ft_strchr(pipex->command->argv[0], '/'))
	{
		pipex->command->path = pipex->command->argv[0];
		if (!check_exists_and_not_dir(pipex->command->path) && !errno)
			error_and_exit(pipex, PROG_FILE_IS_DIR);
	}
	else
	{
		ind = get_path_index(pipex->env);
		if (ind == -1)
		{
			pipex->command->path = pipex->command->argv[0];
			return ;
		}
		pipex->path_split = get_path_split(pipex->env, (size_t)ind);
		if (!pipex->path_split)
			error_and_exit(pipex, MALLOC_FAIL);
		handle_command(pipex->path_split, pipex);
	}
}

void	get_command(t_pipex *pipex)
{
// TODO: handled outside, remove input_arg logic from here
	//pipex->command->input_arg = argv[pipex->current_command];
// handled outside
// TODO: combine arg array with first param
// free internals somewhere
	pipex->command->argv = get_command_argv(pipex->command[pipex->current_command]);
	if (!pipex->command->argv)
		error_and_exit(pipex, MALLOC_FAIL);
//  TODO: special case, needs handling?
/*	if (*(pipex->command->argv) == 0)
	{
		free_split(pipex->command->argv);
		pipex->command->argv = get_alt_argv(argv[pipex->current_command]);
		if (pipex->command->argv == NULL)
			error_and_exit(pipex, MALLOC_FAIL);
	}
*/
// TODO: OK????
	resolve_command_path(pipex);
	pipex->command->env = pipex->env;
}
