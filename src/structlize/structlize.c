/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structlize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:27:51 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/12 22:18:46 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_nullize_struct(t_cmd *new_cmd)
{
	ft_bzero(new_cmd, sizeof(t_cmd));
	new_cmd->heredoc_fd = -1;
}

void	ft_add_redirection(t_shell *shell, char ***array, char *file)
{
	*array = ft_add_to_array(shell, *array, file);
}

void	struct_else(t_shell *shell, t_cmd *cc, int *i)
{
	if (cc != NULL && cc->cmd_name == NULL)
	{
		cc->cmd_name = ft_strdup(shell->tokens[*i]);
		if (!cc->cmd_name)
			malloc_fail_clean_exit(shell);
	}
	else
		cc->arg = ft_add_to_array(shell, cc->arg, shell->tokens[*i]);
}

int	is_array_member(char *str, char **arr)
{
	int	j;

	j = 0;
	while (arr && arr[j])
	{
		if (str && arr[j] && str == arr[j])
		{
			return (1);
		}
		j++;
	}
	return (0);
}

void	ft_structlize(t_shell *shell)
{
	t_cmd	*current_cmd;

	current_cmd = NULL;
	loop_tokens(shell, current_cmd);
	if (shell->err_code == 2)
	{
		clear_cmds(shell);
		shell->exit_code = 2;
	}
}
