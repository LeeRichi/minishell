/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_ops_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:32:51 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/04/04 16:16:13 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error_message(t_error error)
{
	char	*error_message;

	error_message = 0;
	if (is_known_errtype(error))
	{
		if (error.errtype == MALLOC_FAIL)
			perror("Malloc fail");
		else
			error_message = get_error_message(error);
	}
	else
	{
		perror("Unspecified error");
	}
	if (error_message)
	{
		ft_putendl_fd(error_message, 2);
		free(error_message);
	}
}

void	error_and_exit(t_pipex *pipex, t_error error)
{
	t_shell		*shell;
	t_perrtypes	errtype;

	errtype = error.errtype;
	print_error_message(error);
	shell = 0;
	if (pipex)
	{
		shell = (t_shell *)pipex->shell;
		ft_free_all(shell);
		shell->pipex = 0;
	}
	resolve_exit_code(errtype);
}
