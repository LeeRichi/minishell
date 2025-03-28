/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:31:10 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/28 18:24:32 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	char	*path_str;

	path_str = envp[ind] + 5;
	return (ft_split(path_str, ':'));
}

int	resolve_heredoc_cmds(t_cmd *cmds, size_t command_count)
{
	size_t	i;

	i = 0;
	while (i < command_count)
	{
		if (check_heredoc(cmds[i]))
		{
			cmds[i].heredoc_fd = get_cmd_heredoc(cmds[i]);
			if (cmds[i].heredoc_fd == -1)
				return (0);
		}
		else
			cmds[i].heredoc_fd = -1;
		i++;
	}
	return (1);
}

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
		cmds = cmds->next;
		i++;
	}
	return (arr);
}
