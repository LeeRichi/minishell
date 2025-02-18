/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:38:17 by chlee2            #+#    #+#             */
/*   Updated: 2025/02/16 18:10:14 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void handle_cd(char **tokens, t_shell *shell)
{
    if (tokens[1])
    {
        if (chdir(tokens[1]) != 0)
		{
            perror("cd");
			shell->exit_code = 1;
		}
    }
    else
    {
        char *home = getenv("HOME");
        if (home)
            chdir(home);
        else
            printf("HOME not set.\n");
    }
	return (0);
}
