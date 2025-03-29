/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:45:12 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/29 21:01:14 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_pwd(t_shell *shell)
{
	char	*value;
	char	path[PATH_MAX];

	value = ft_getenv_value_ptr("PWD", shell);
	if (value)
	{
		ft_putendl_fd(value, 1);
		return (SUCCESS);
	}
	else
	{
		if (getcwd(path, PATH_MAX))
		{
			ft_putendl_fd(path, 1);
			return (SUCCESS);
		}
		shell->exit_code = ERROR;
		return (ERROR);
	}
}
