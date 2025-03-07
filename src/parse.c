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

void parse(t_shell *shell)
{
	tokenize_input(shell->input, shell);

	if (shell->tokens)
        print_tokens(shell->tokens);

    if (!shell->err_code)
		ft_structlize(shell);
	if (!shell->err_code)
	{
		print_cmd_struct(shell->cmds);
		//pipex_launch(shell->cmds, shell->envp);
	}
	else
		shell->err_code = 0;

	// if (shell->tokens && shell->tokens[0] != NULL)
    // {
	// 	if (strcmp(shell->tokens[0], "echo") == 0)
    //         handle_echo(shell->tokens, shell);
    //     else if (strcmp(shell->tokens[0], "cd") == 0)
    //         handle_cd(shell->tokens, shell);
    //     else if (strcmp(shell->tokens[0], "pwd") == 0)
    //         handle_pwd(shell);
    //     else if (strcmp(shell->tokens[0], "exit") == 0)
    //         handle_exit(shell, shell->tokens);
    //     else if (strcmp(shell->tokens[0], "env") == 0)
    //        handle_env(shell->envp); // Pass environment variables
    //     else if (strcmp(shell->tokens[0], "unset") == 0)
    //         handle_unset(shell);
    //     else if (contains_str(shell->tokens, "export")) //this is tricky one, cause export does not need to be the first argument?
    //         handle_export(shell);
        // else
        //     execute_external_command(shell->tokens);
        // might delete depends how I free_all?
	// }

	// freeing
	// if (shell->tokens)
	// {
	// 	free_tokens(shell->tokens);
	// 	shell->tokens = 0;
	// }

    shell->ambiguous_flag = 0;
}
