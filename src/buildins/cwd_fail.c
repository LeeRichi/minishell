/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd_fail.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:04:35 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/28 17:39:29 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cwd_fail(t_shell *shell, char **custom)
{
	ft_printf_fd(STDERR,
		"getcwd: cannot access parent directories: No such file or directory\n");
	shell->exit_code = 1;
	free_matrix(custom);
	return (1);
}
