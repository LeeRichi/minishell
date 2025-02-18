/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:38:17 by chlee2            #+#    #+#             */
/*   Updated: 2025/02/14 17:40:46 by chlee2           ###   ########.fr       */
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
}
