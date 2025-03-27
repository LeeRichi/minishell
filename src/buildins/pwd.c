/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:45:12 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/27 14:26:02 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_pwd(t_shell *shell)
{
	char *value;

	value = ft_getenv("PWD", shell);
	if (shell->envp && value)
	{
		ft_putendl_fd(value, 1);
		return (SUCCESS);
	}
	else
	{
		shell->exit_code = ERROR;
		return (ERROR);
	}
}
