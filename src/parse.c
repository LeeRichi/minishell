#include "../includes/minishell.h"

//exe part
void execute_external_command(char **tokens)
{
    pid_t pid = fork();

	if (pid == -1)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        // Child process: execute external command
        if (execvp(tokens[0], tokens) == -1)
        {
            perror(tokens[0]);
            exit(1);
        }
    }
    else
    {
        // Parent process: wait for child to finish
        wait(NULL);
    }
}

void parse(t_shell *shell)
{
	tokenize_input(shell->input, shell);

    // if (shell->tokens)
    //     print_tokens(shell->tokens);
/*
    if (shell->ambiguous_flag)
        printf(YELLOW "global shell ambiguous flag: %d, meaning to print the Error message will be needed.\n\n" RESET, shell->ambiguous_flag);
    else
        printf(GREEN "global shell ambiguous flag: %d\n\n" RESET, shell->ambiguous_flag);
*/

    if (!shell->err_code)
	{
        ft_structlize(shell);
	}

	// printing purpose
	if (!shell->err_code)
	{
//		print_cmd_struct(shell->cmds);
//		pipex_launch(shell->cmds, shell->envp);
	}
	else
		shell->err_code = 0;

/*
    if (shell->tokens && shell->tokens[0] != NULL)
    {
        if (strcmp(shell->tokens[0], "echo") == 0)
            handle_echo(shell->tokens);
        // else if (strcmp(shell->tokens[0], "cd") == 0)
        //     handle_cd(shell->tokens);
        // else if (strcmp(shell->tokens[0], "pwd") == 0)
        //     handle_pwd();
        // else if (strcmp(shell->tokens[0], "exit") == 0)
        //     handle_exit(shell, shell->tokens);
        // else if (strcmp(shell->tokens[0], "env") == 0)
        //     handle_env(shell->envp); // Pass environment variables
        // else if (strcmp(shell->tokens[0], "unset") == 0)
        //     handle_unset(shell->tokens);
        // else if (strcmp(shell->tokens[0], "export") == 0)
        //     handle_export(shell->tokens);
        // else
        //     execute_external_command(shell->tokens);
        // might delete depends how I free_all?
    }
*/
    // if (shell->tokens)
    //     free_tokens(shell->tokens);

    shell->ambiguous_flag = 0;
}
