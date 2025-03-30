/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:10:48 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/30 21:05:38 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void print_tokens(char **tokens)
// {
//     int i;

//     printf("\n");
//     i = 0;
//     while (tokens[i])
//     {
//         printf("Token %d: %s\n", i, tokens[i]);
//         // printf("%s\n", tokens[i]);
// 		i++;
// 	}
//     printf("\n");
// }

// void print_cmd_struct(t_cmd *cmd)
// {
//     // t_cmd *head = cmd;

//     printf("---------Start---------\n");

//     // while (cmd)
//     // {
//     //     if (cmd->ambiguous_flag_node)
//     //         printf(RED "Warning, this link-list contains ambiguous node(s)!!\n" RESET);
//     //     cmd = cmd->next;
//     // }
//     // cmd = head;

//     int command_index = 1;  // To track the command index in the linked list
//     while (cmd)
//     {
//         // Print arguments if any
//         if (cmd->ambiguous_flag_node)
//             printf(RED "This is an ambiguous node!!\n" RESET);

//         printf("Command %d:\n", command_index++);
//         printf("Command Name: %s\n", cmd->cmd_name ? cmd->cmd_name : "NULL");

//         if (cmd->arg)
//         {
//             printf("Arguments: ");
//             for (int i = 0; cmd->arg[i]; i++)
//                 printf("%s ", cmd->arg[i]);
//             printf("\n");
//         }
//         int file_counter = 0;
//         // Print input files if any
//         if (cmd->infiles)
//         {
//             printf("Input Files: ");
//             for (int i = 0; cmd->infiles[i]; i++)
//             {
//                 printf("%s ", cmd->infiles[i]);
//                 file_counter++;
//             }
//             printf("\n");
//         }

//         // Print output files if any
//         if (cmd->outfiles)
//         {
//             printf("Output Files: ");
//             for (int i = 0; cmd->outfiles[i]; i++)
//             {
//                 printf("%s ", cmd->outfiles[i]);
//                 file_counter++;
//             }
//             printf("\n");
//         }

//         //cat < 1 > 2 >> 3
//         // if (cmd->type)
//         // {
//             printf("Types: \n");
//             for (int i = 0; i < file_counter; i++)
//             {
//                 // printf("i: %d\n", i);
//                 // printf("yooo: %u\n", cmd->redirect_type[i]);
// 				printf("%s \n", get_redirection_type_string(cmd->redirect_type[i]));
//             }
//         // }

//         // Print pipe flag
//         printf("Pipe: %d\n", cmd->pipe);

//         // Print the "next" pointer information to show it's a linked list
//         // if (cmd->next)
//         //     printf("Next Command: %p\n", (void *)cmd->next);
//         // else
//         //     printf("Next Command: NULL\n");


//         if (cmd->next)
//         {
//             printf("Next Command: %p\n", (void *)cmd->next);
//             printf("  |\n");
//             printf("  |\n");
//             printf("  V\n");
//         }

//         // Move to the next command in the list
//         cmd = cmd->next;
//         // printf("\n");  // Adding a newline between commands for better readability
//     }
//     printf("----------End----------\n\n");
// }

void	parse(t_shell *shell)
{
	tokenize_input(shell->input, shell);


	// if (shell->tokens)
	// {
    //     print_tokens(shell->tokens);
	// }

	if (!shell->err_code && shell->tokens)
		ft_structlize(shell);

	// if (!shell->err_code)
	// {
	// 	print_cmd_struct(shell->cmds);
	// 	//pipex_launch(shell->cmds, shell->envp);
	// }
	
	shell->err_code = 0;
	shell->ambiguous_flag = 0;
}
