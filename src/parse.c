#include "../includes/minishell.h"

//exe part //old
// void execute_external_command(char **tokens)
// {
//     pid_t pid = fork();

// 	if (pid == -1)
//     {
//         perror("fork");
//         return;
//     }

//     if (pid == 0)
//     {
//         // Child process: execute external command
//         if (execvp(tokens[0], tokens) == -1)
//         {
//             perror(tokens[0]);
//             exit(1);
//         }
//     }
//     else
//     {
//         // Parent process: wait for child to finish
//         wait(NULL);
//     }
// }

int contains_str(char **tokens, char *str)
{
	int i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], str) == 0)
			return (1);
		i++;
	}
	return (0);
}

// void extra_care_for_dollar(t_shell *shell)
// {
//     int token_i;
//     int j;
//
//     token_i = 0;
//     while (shell->tokens[token_i])
//     {
//         j = 0;
//         while (shell->tokens[token_i][j])
//         {
//             if (shell->tokens[token_i][j] == '$' && shell->tokens[token_i][j + 1] == '?')
//             {
//                 char *exit_code_str = ft_itoa(shell->exit_code);
//                 int exit_code_len = ft_strlen(exit_code_str);
//                 ft_memmove(&shell->tokens[token_i][j], &shell->tokens[token_i][j + 1], ft_strlen(&shell->tokens[token_i][j + 1]) + 1);
//                 ft_memcpy(&shell->tokens[token_i][j], exit_code_str, exit_code_len);
//                 j += exit_code_len - 1;
//                 free(exit_code_str);
//             }
//             j++;
//         }
//         token_i++;
//     }
// }

// void final_check(t_shell *shell)
// {
//     int i = 0;
//     int j = 0;
//     int s_count = 0;
//     int d_count = 0;
//     char *str = NULL;
//     int original_len = 0;
//     int sign_location = 0;

//     while (shell->tokens[i])
//     {
//         if (ft_strchr(shell->tokens[i], '$')) //has sign
//         {
//             while (shell->tokens[i][j] != '$')
//             {
//                 if (shell->tokens[i][j] == '\'')
//                     s_count++;
//                 else if (shell->tokens[i][j] == '"')
//                     d_count++;
//                 j++;
//             }
//             original_len = ft_strlen(shell->tokens[i]);
//             sign_location = i;
//             break ;
//         }
//         else
//             return ;
//         i++;
//     }
//      if (s_count % 2 == 0 && d_count % 2 == 0)
//     {
//         if (sign_location >= 0 && shell->tokens[sign_location])  // Check valid token
//         {
//             str = shell->tokens[sign_location] + j + 1;  // Skip the '$' sign
//             if (str == NULL)  // Check if str is valid
//             {
//                 fprintf(stderr, "Error: invalid string at str\n");
//                 return;
//             }

//             // Find the length of the variable name
//             int name_len = 0;
//             while (str[name_len] != '\0' && str[name_len] != '\'' && str[name_len] != '"'
//                    && (isalnum(str[name_len]) || str[name_len] == '_'))
//             {
//                 name_len++;
//             }

//             // Allocate memory for the variable name
//             char *name = malloc(name_len + 1);
//             if (name == NULL)
//             {
//                 perror("malloc");
//                 return;
//             }

//             // Copy the variable name
//             ft_strlcpy(name, str, name_len + 1);

//             // Look up the environment variable
//             char *value = ft_getenv(name, shell);
//             if (value)
//             {
//                 int value_len = ft_strlen(value);

//                 // Allocate memory for the expanded string (original part + value + remaining part)
//                 int expanded_len = (original_len - (j + 1)) + value_len + 1;
//                 char *expanded_str = malloc(expanded_len);
//                 if (expanded_str == NULL)
//                 {
//                     perror("malloc");
//                     free(name);
//                     return;
//                 }

//                 // Copy the part of the string before the variable
//                 strncpy(expanded_str, shell->tokens[sign_location], j);

//                 // Copy the value of the environment variable
//                 strcpy(expanded_str + j, value);

//                 // Copy the part of the string after the variable name
//                 strcpy(expanded_str + j + value_len, str + name_len);

//                 // Update the token with the expanded string
//                 free(shell->tokens[sign_location]);
//                 shell->tokens[sign_location] = expanded_str;
//             }

//             // Free the name after use
//             free(name);
//         }
//         else
//         {
//             fprintf(stderr, "Error: invalid sign_location or token\n");
//         }
//     }
// }

void parse(t_shell *shell)
{
	tokenize_input(shell->input, shell);

	// if (shell->tokens)
    //     print_tokens(shell->tokens);

    if (!shell->err_code && shell->tokens)
    {
		ft_structlize(shell);
    }
	// if (!shell->err_code)
	// {
	// 	print_cmd_struct(shell->cmds);
	// 	//pipex_launch(shell->cmds, shell->envp);
	// }

	// else
    //     shell->err_code = 0;


    //try to alway call this so it doesnt affect the next input
 	shell->err_code = 0;
	shell->ambiguous_flag = 0;
}
