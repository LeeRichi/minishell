/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:31:10 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/02/06 22:00:46 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "../../includes/minishell.h"
/*
int	count_split(char **texts)
{
	int	i;

	i = 0;
	while (texts[i])
	{
		i++;
	}
	return (i);
}
*/
char	**ft_shallow_split_join(char **tab1, char **tab2)
{
	char	**new_tab;
	int		tab1_length;
	int		tab2_length;
	int		i;

	i = 0;
	tab1_length = count_split(tab1);
	tab2_length = count_split(tab2);
	new_tab = ft_calloc(tab1_length + tab2_length + 1, sizeof(char *));
	if (!new_tab)
		return (0);
	while (i < (tab1_length + tab2_length))
	{
		if (i < tab1_length)
			new_tab[i] = tab1[i];
		else
			new_tab[i] = tab2[i - tab1_length];
		i++;
	}
	return (new_tab);
}

char	**get_command_argv(t_cmd cmd)
{
	char	*tab_cmd_name[2];
	char	*empty_args[1];

	tab_cmd_name[0] = cmd.cmd_name;
	tab_cmd_name[1] = 0;
	empty_args[0] = 0;
	if (cmd.arg)
		return (ft_shallow_split_join(tab_cmd_name, cmd.arg));
	else
		return (ft_shallow_split_join(tab_cmd_name, empty_args));
}

char	**get_path_split(char **envp, size_t ind)
{
	envp[ind] += 5;
	return (ft_split(envp[ind], ':'));
}
/*
t_pipex_command	cmd_to_pipex_command(t_cmd cmd, char **envp)
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
*/
/* TODO: keep in mind order of freeing */

t_cmd	*cmd_list_to_arr(t_cmd *cmds, size_t command_count)
{
	t_cmd	*arr;
	size_t	i;

	i = 0;
	arr = malloc((command_count + 1) * sizeof(t_cmd));
	if (!arr)
		return (0);
	ft_bzero(&arr[command_count], sizeof(t_cmd));
	while (i < command_count)
	{
		arr[i] = *cmds;
		cmds = cmds->next;
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
	pipex.command = cmd_list_to_arr(commands, command_count);
//TODO: free list
	pipex.path_split = 0;
	return (pipex);
}

//t_command	*free_command_content(t_command *command)
t_cmd	*free_command_content(t_cmd *command)
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
