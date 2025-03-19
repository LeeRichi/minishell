/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:45:06 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/19 15:04:16 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int handle_echo(char **cmd_args, t_shell *shell)
{
    //printf("hi\n");
    
    (void)shell;
    int i = 0;
    int newline = 1;

	// int invalid = 0;

    if (!cmd_args)
    {
        printf("\n");
        return (0);
    }
	
    // if (cmd_args[0] && (ft_strcmp(cmd_args[0], "-n")) == 0)
    if (cmd_args[i] && cmd_args[i][0] =='-')
    {
        while(cmd_args[i]) //loop each string
        {
            int j = 1;
            while (cmd_args[i][j])
            {
                if (cmd_args[i][j] != 'n')
                {
					
					int temp = i;
					while (cmd_args[temp])
					{
						printf("%s", cmd_args[temp]);
						if (cmd_args[temp + 1])
							printf(" ");
						temp++;
					}
                }
				else
					newline = 0;
                j++;
            }
            i++;
        }
    }
	else
	{
		while (cmd_args[i])
		{
			printf("%s", cmd_args[i]);
			if (cmd_args[i + 1])
				printf(" ");
			i++;
		}
	}

	// if (!invalid)
	// {
	// 	while (cmd_args[i])
	// 	{
	// 		printf("%s", cmd_args[i]);
	// 		if (cmd_args[i + 1])
	// 			printf(" ");
	// 		i++;
	// 	}
	// }
    
    if (newline)
        printf("\n");

    return (0);
}


// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   echo.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/01/06 19:45:06 by chlee2            #+#    #+#             */
// /*   Updated: 2025/03/17 15:45:01 by chlee2           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// int handle_echo(char **cmd_args, t_shell *shell)
// {
//     //printf("hi\n");
    
//     (void)shell;
//     int i = 0;
//     int newline = 1;

//     if (!cmd_args)
//     {
//         return (0);
//     }
//     if (cmd_args[0] && ft_strcmp(cmd_args[0], "-n") == 0)
//     {
//         newline = 0;
//         i++;
//     }
//     // else if (cmd_args[1] && cmd_args[1][0] == '-')
//     // {
//     //     printf("test\n");
// 	// 	fprintf(stderr, "echo: invalid option -- '%s'\n", cmd_args[1]);
// 	// 	shell->exit_code = 1;
//     // }
//     //i++;
//     while (cmd_args[i])
//     {
//         printf("%s", cmd_args[i]);
//         if (cmd_args[i + 1])
//             printf(" ");
//         i++;
//     }
    
//     if (newline)
//         printf("\n");

//     return (0);
// }