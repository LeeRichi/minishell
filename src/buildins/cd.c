/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:38:17 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/20 18:52:35 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int handle_cd(char **args, t_shell *shell)
{
	char *home;
	
	if (!args || ft_strcmp(args[0], "--") == 0)
	{
		home = ft_getenv("HOME", shell);
		if (home)
		{
			chdir(home);
			free(home);
		}
		else
		{
			printf("HOME not set.\n");
			shell->exit_code = 1;
			return (1);
		}
	}
	else if (args[0])
	{
		if (args [1])
		{
			// perror(" too many arguments");
			ft_printf_fd(STDERR, " too many arguments\n");
			shell->exit_code = 1;
			return (1);
		}
		if (chdir(args[0]) != 0)
		{
			if (ft_strcmp(args[0], "-") == 0)
			{				
				return (0);
			}
			// perror("cd");
			else
			{
				ft_printf_fd(STDERR, " cd\n");
				shell->exit_code = 1;
				return (1);
			}
		}
	}
	return (0);
}
