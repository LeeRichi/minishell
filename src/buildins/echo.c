/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:45:06 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/07 20:31:55 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void handle_echo(char **cmd_args, t_shell *shell)
{
    (void)shell;
    int i = 0;
    int newline = 1;
    
    
    if (cmd_args[0] && strcmp(cmd_args[0], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    // else if (cmd_args[1] && cmd_args[1][0] == '-')
    // {
    //     printf("test\n");
	// 	fprintf(stderr, "echo: invalid option -- '%s'\n", cmd_args[1]);
	// 	shell->exit_code = 1;
    // }
    //i++;
    while (cmd_args[i])
    {
        printf("%s", cmd_args[i]);
        if (cmd_args[i + 1])
            printf(" ");
        i++;
    }
    
    if (newline)
        printf("\n");
}
