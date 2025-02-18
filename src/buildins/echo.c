/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:45:06 by chlee2            #+#    #+#             */
/*   Updated: 2025/02/14 17:41:42 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void handle_echo(char **tokens, t_shell *shell)
{
    (void)shell;
    int i = 1;
    int newline = 1;

    if (tokens[1] && strcmp(tokens[1], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    // else if (tokens[1] && tokens[1][0] == '-')
    // {
    //     printf("test\n");
	// 	fprintf(stderr, "echo: invalid option -- '%s'\n", tokens[1]);
	// 	shell->exit_code = 1;
    // }
    while (tokens[i])
    {
        printf("%s", tokens[i]);
        if (tokens[i + 1])
            printf(" ");
        i++;
    }
    if (newline)
        printf("\n");
}