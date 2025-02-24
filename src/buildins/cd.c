/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:38:17 by chlee2            #+#    #+#             */
/*   Updated: 2025/02/18 21:42:16 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void handle_cd(char **args, t_shell *shell)
{
	printf("%p\n", shell);
	if (!args)
	{
		char *home = getenv("HOME");
		if (home)
			chdir(home);
		else
			printf("HOME not set.\n");
	}
	if (args[0])
	{
		if (chdir(args[0]) != 0)
		{
			perror("cd");
			shell->exit_code = 1;
		}
	}
}
