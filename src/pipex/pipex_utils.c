/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:31:10 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/10 21:17:24 by mbutuzov         ###   ########.fr       */
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
	char *path_str;

	path_str = envp[ind] + 5;
//	envp[ind] += 5;
	return (ft_split(path_str, ':'));
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

int resolve_heredoc_cmds(t_cmd *cmds, size_t command_count)
{
	size_t i;

	i = 0;
	while(i < command_count)
	{
		if (check_heredoc(cmds[i]))
		{
			cmds[i].heredoc_fd = get_cmd_heredoc(cmds[i]);
			if (cmds[i].heredoc_fd == -1)
			{
				/* TODO: error handle, array cleanup? list cleanup separately */
				/* ft_free_all
				exit or return
				cleanup previous heredocs?
*/
				return (0);
			}
		}
		else
			cmds[i].heredoc_fd = -1;
		i++;
	}
	return (1);
}

//t_cmd	*cmd_list_to_arr_resolve_hd(t_cmd *cmds, size_t command_count, t_shell *shell)
t_cmd	*cmd_list_to_arr(t_cmd *cmds, size_t command_count, t_shell *shell)
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
		arr[i].shell = (void *)shell;
/*
		if (check_heredoc(*cmds))
		{
			arr[i].heredoc_fd = get_cmd_heredoc(*cmds);
			if (arr[i].heredoc_fd == -1)
			{
				TODO: error handle, array cleanup? list cleanup separately
			}
		}
		else
			arr[i].heredoc_fd = -1;
*/
		cmds = cmds->next;
		i++;
	}
	return (arr);
}

t_pipex	get_pipex(size_t command_count, t_cmd *commands, char **envp, t_shell *shell)
{
	t_pipex	pipex;

	pipex.command_count = command_count;
	pipex.current_command = 0;
	pipex.shell = (void *)shell;
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
	pipex.command = cmd_list_to_arr(commands, command_count, shell);
	pipex.path_split = 0;
	return (pipex);
}

//t_command	*free_command_content(t_command *command)
//wip, careful here
t_cmd	*free_pipex_cmd(t_cmd *command)
{
	while (command->cmd_name || command->infiles || command->outfiles)
	{
		if (command->argv)
		{
//			if (command->path && command->argv[0] == command->path)
//				command->path = 0;
//			free_split(command->argv);
		//	ft_putstr_fd("before freeing command argv\n", 2);
			free(command->argv);
			command->argv = 0;
		}
		if (command->path && command->path != command->cmd_name)
		{
			free(command->path);
			command->path = 0;
		}
/*		if (command->cmd_name)
		{
			free(command->cmd_name);
			command->cmd_name = 0;
		}
*/
		if (command->heredoc_fd != -1)
		{
			close(command->heredoc_fd);
			command->heredoc_fd = -1;
		}
		command++;
/*		if (command->arg)
		{
			free_split(command->arg);
			command->arg = 0;
		}
		if (command->infiles)
		{
			
		}
		if (command->outfiles)
		{
		}
		if (command->heredoc_fd)
		{
		}
*/
	}
	return (0);
}

void	free_pipex(t_pipex pipex)
{
	if (pipex.command)
	{
		free_pipex_cmd(pipex.command);
		free(pipex.command);
		pipex.command = 0;
	}
	if (pipex.path_split)
		free_split(pipex.path_split);
	ft_close(&pipex.pipe[0]);
	ft_close(&pipex.pipe[1]);
	ft_close(&pipex.reserve_fd);
}
