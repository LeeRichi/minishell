/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:21:50 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/04/03 18:48:29 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	resolve_exit_code(t_perrtypes errtype)
{
	if (errtype == CMD_NOT_FOUND || errtype == CMD_FILE_NOT_FOUND)
		exit(127);
	if (errtype == EXECVE_FAIL || errtype == PROG_FILE_IS_DIR)
		exit(126);
	exit(EXIT_FAILURE);
}

t_error	error_init(t_perrtypes errtype, char *file_name, char *command_name)
{
	t_error	error;

	error.errtype = errtype;
	error.f_name = file_name;
	error.cmd_name = command_name;
	return (error);
}

char	*form_err_m(char *str1, char *str2, char *str3)
{
	char	*arr[4];
	char	sep[3];

	sep[0] = ':';
	sep[1] = ' ';
	sep[2] = 0;
	arr[0] = str1;
	arr[1] = str2;
	arr[2] = str3;
	arr[3] = 0;
	return (ft_split_join(arr, sep));
}

int	is_known_errtype(t_error err)
{
	t_perrtypes	type;

	type = MALLOC_FAIL;
	while (type <= AMBIGOUS_REDIR)
	{
		if (err.errtype == type)
			return (1);
		type++;
	}
	return (0);
}

char	*get_error_message(t_error err)
{
	if (err.errtype == CMD_NOT_FOUND)
		return (form_err_m(err.cmd_name, "command not found", 0));
	else if (err.errtype == PERMISSION_FAIL)
		return (form_err_m(SHELL_NAME, err.f_name, strerror(EACCES)));
	else if (err.errtype == FILE_NOT_FOUND)
		return (form_err_m(SHELL_NAME, err.f_name, strerror(ENOENT)));
	else if (err.errtype == PROG_FILE_IS_DIR)
		return (form_err_m(SHELL_NAME, err.cmd_name, strerror(EISDIR)));
	else if (err.errtype == DUP_FAIL)
		return (form_err_m(SHELL_NAME, "dup fail", strerror(errno)));
	else if (err.errtype == PIPE_FAIL)
		return (form_err_m(SHELL_NAME, "pipe fail", strerror(errno)));
	else if (err.errtype == EXECVE_FAIL)
		return (form_err_m(SHELL_NAME, err.cmd_name, strerror(errno)));
	else if (err.errtype == CMD_FILE_NOT_FOUND)
		return (form_err_m(SHELL_NAME, err.cmd_name, strerror(ENOENT)));
	else if (err.errtype == FILE_REDIR_FAIL)
		return (form_err_m(SHELL_NAME, err.f_name, strerror(errno)));
	else if (err.errtype == FORK_FAIL)
		return (form_err_m(SHELL_NAME, "fork fail", strerror(errno)));
	else if (err.errtype == HEREDOC_FAIL)
		return (form_err_m(SHELL_NAME, "heredoc fail", strerror(errno)));
	else if (err.errtype == AMBIGOUS_REDIR)
		return (form_err_m(SHELL_NAME, "ambigous redirect", 0));
	return (0);
}
