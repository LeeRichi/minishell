/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structlize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:27:51 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/04 20:32:43 by chlee2           ###   ########.fr       */
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

static void	struct_else(t_shell *shell, t_cmd *cc, int *i)
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

// int ft_strcmp_deb(char *s1, char *s2, int line)
// {
// 	static int sad =0;
// 	sad++;
// 	printf("strcmd line %d\n", line);
// 	if (sad > 2)
// 		ft_printf("s1 at strcmp %s\n", s1);
// 	printf("strcmd line %s\n", s1);
// 	return (ft_strcmp(s1, s2));
// }

// #define ft_strcmp(x,y)  ft_strcmp_deb(x,y,__LINE__)

static void	loop_tokens(t_shell *shell, t_cmd *current_cmd)
{
	int		i;
	t_cmd	*new_cmd;

	// int j = 0;
	// while (shell->tokens[j])
	// {
	// 	printf("fuckkkk: %s\n", shell->tokens[2]);
	// 	j++;
	// }
	// if (!shell->tokens[2])
	// 	pf

	new_cmd = NULL;
	i = 0;
	while (shell->tokens[i]) //3
	{
		// if (shell->tokens[i] == "")
		// {
			
		// }
		// printf("i: %d\n", i);
		if (current_cmd == NULL || ft_strcmp(shell->tokens[i], "|") == 0)
		{
			// printf("fuck1\n");
			allocate_nodes(&current_cmd, &new_cmd, shell);
			if (ft_strcmp(shell->tokens[i], "|") == 0)
				i++;
				
		}
		if (!shell->tokens[i])
		//TODO: think
			break;
		if (ft_strcmp(shell->tokens[i], "<<") == 0
			|| ft_strcmp(shell->tokens[i], ">>") == 0
			|| ft_strcmp(shell->tokens[i], ">") == 0
			|| ft_strcmp(shell->tokens[i], "<") == 0)
			struct_redir(shell, current_cmd, &i);
		else
			struct_else(shell, current_cmd, &i);
		// printf("i: %d\n", i);

		// if (!shell->tokens[i])
		// 	break;
		i++;
	}
}

void	ft_structlize(t_shell *shell)
{
	t_cmd	*current_cmd;

	current_cmd = NULL;
	loop_tokens(shell, current_cmd);
	if (current_cmd)
		current_cmd->redirection_index = 0;
	if (shell->err_code == 2)
	{
		clear_cmds(shell);
		shell->exit_code = 2;
	}
}
