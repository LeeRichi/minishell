/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:46:08 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/02/05 21:29:25 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "pipex.h"
//#include "minishell.h"
#include "../../includes/minishell.h"

int	check_exists_and_not_dir(char *path)
{
	int	fd;

	if (access(path, F_OK) == 0)
	{
		fd = open(path, O_DIRECTORY);
		if (fd == -1)
		{
			if (errno == ENOTDIR)
				return (1);
			return (0);
		}
		else
		{
			close(fd);
			return (0);
		}
	}
	return (0);
}

static int	count_command_in_path(char *filename, char **paths)
{
	char	*command_path;
	int		count;

	count = 0;
	while (*paths)
	{
		command_path = ft_strjoin(*paths, filename);
		if (!command_path)
			return (0);
		if (check_exists_and_not_dir(command_path))
			count++;
		free(command_path);
		paths++;
	}
	return (count);
}

static char	*check_command_path_exist(char *filename, char **paths, int to_skip)
{
	char	*command_path;

	while (*paths)
	{
		command_path = ft_strjoin(*paths, filename);
		if (!command_path)
			return (0);
		if (check_exists_and_not_dir(command_path))
		{
			if (to_skip)
				to_skip--;
			else
				return (command_path);
		}
		free(command_path);
		paths++;
	}
	return (0);
}

char	*get_command_path(char *filename, char **paths)
{
	char	*path;
	int		count;
	int		i;

	i = 0;
	count = count_command_in_path(filename, paths);
	if (count == 0)
		return (0);
	else if (count == 1)
	{
		return (check_command_path_exist(filename, paths, 0));
	}
	while (i < count)
	{
		if (i == (count - 1))
			return (check_command_path_exist(filename, paths, i));
		path = check_command_path_exist(filename, paths, i);
		if (!path)
			return (0);
		else if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (0);
}
