/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structlize_p3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:01:09 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/12 22:07:15 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//current_cmd ==cc
//new_cmd == nc
void	allocate_nodes(t_cmd **current_cmd, t_cmd **nc, t_shell *shell)
{
	size_t	rc;

	rc = cr(shell->tokens);
	if (*current_cmd)
		(*current_cmd)->pipe = 1;
	*nc = malloc(sizeof(t_cmd));
	if (!(*nc))
		malloc_fail_clean_exit(shell);
	ft_nullize_struct(*nc);
	(*nc)->redirect_type = ft_calloc(cr(shell->tokens),
			sizeof(t_redirect_type));
	(*nc)->outfiles = ft_calloc((cs(shell->tokens, ">") + 1), sizeof(char *));
	(*nc)->infiles = ft_calloc((cs(shell->tokens, "<") + 1), sizeof(char *));
	if (!(*nc)->redirect_type || !(*nc)->outfiles || !(*nc)->infiles)
		malloc_fail_clean_exit(shell);
	if (*current_cmd)
		(*current_cmd)->next = *nc;
	else
		shell->cmds = *nc;
	*current_cmd = *nc;
}

void	handle_redirection(t_shell *shell, t_cmd *cc, char *op, char *file)
{
	int	i;

	i = cc->redirection_index;
	if (ft_strcmp(op, "<") == 0)
	{
		ft_add_redirection(shell, &cc->infiles, file);
		cc->redirect_type[i] = INPUT_REDIRECT;
	}
	else if (ft_strcmp(op, ">") == 0 || ft_strcmp(op, ">>") == 0)
	{
		ft_add_redirection(shell, &cc->outfiles, file);
		if (ft_strcmp(op, ">") == 0)
			cc->redirect_type[i] = OUTPUT_REDIRECT;
		else
			cc->redirect_type[i] = APPEND_REDIRECT;
	}
	else if (ft_strcmp(op, "<<") == 0)
	{
		ft_add_redirection(shell, &cc->infiles, file);
		cc->redirect_type[i] = HERE_DOC;
	}
	cc->redirection_index = i + 1;
}

static void	syntax_err_print_v2(t_shell *shell)
{
	ft_printf_fd(STDERR, "minishell: syntax error\n");
	shell->err_code = 2;
	shell->exit_code = 2;
}

void	struct_redir_helper(t_shell *shell, t_cmd *cc, int i)
{
	handle_redirection(shell, cc, shell->tokens[i], shell->tokens[i + 1]);
}

//current_cmd == cc
void	struct_redir(t_shell *shell, t_cmd *cc, int *i)
{
	if (shell->tokens[*i + 1] != NULL
		&& ft_start_with_specials(shell->tokens[*i + 1]))
		syntax_err_print_v2(shell);
	else if (shell->tokens[*i + 1] != NULL && shell->tokens[*i + 1][0] == '\0')
		cc->ambiguous_flag_node = 1;
	else if (shell->tokens[*i + 1] != NULL)
	{
		handle_redirection(shell, cc, shell->tokens[*i], shell->tokens[*i + 1]);
		(*i)++;
	}
	else if (shell->tokens[*i + 1] == NULL)
	{
		if (cc->cmd_name)
			cc->arg = ft_add_to_array(shell, cc->arg, shell->tokens[*i]);
		else
		{
			cc->cmd_name = ft_strdup(shell->tokens[*i]);
			if (!cc->cmd_name)
				malloc_fail_clean_exit(shell);
		}
	}
	else if (cc != NULL)
		struct_redir_helper(shell, cc, *i);
	else
		ft_printf_fd(STDERR, "Error: Redirection without a command\n");
}
