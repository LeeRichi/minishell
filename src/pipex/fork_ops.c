/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:28:08 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/02/20 23:10:11 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "pipex.h"
//#include "minishell.h"
#include "../../includes/minishell.h"

static void err_and_exit(char *fname, int line, t_pipex *pipex, t_perrtypes errtype)
{
	printf("%s, %d", fname, line);
	error_and_exit(pipex, errtype);
}
#define error_and_exit(x, y) err_and_exit(__FILE__, __LINE__, x, y)

//int is_builtin(t_cmd cmd)
t_builtin_type get_builtin_type(t_cmd cmd)
{
	if (!cmd.cmd_name)
		return (NOT_BUILTIN);
	if (!ft_strcmp(cmd.cmd_name, "cd"))
		return (IS_CD);
	if (!ft_strcmp(cmd.cmd_name, "echo"))
		return (IS_ECHO);
	if (!ft_strcmp(cmd.cmd_name, "env"))
		return (IS_ENV);
	if (!ft_strcmp(cmd.cmd_name, "exit"))
		return (IS_EXIT);
	if (!ft_strcmp(cmd.cmd_name, "export"))
		return (IS_EXPORT);
	if (!ft_strcmp(cmd.cmd_name, "pwd"))
		return (IS_PWD);
	if (!ft_strcmp(cmd.cmd_name, "unset"))
		return (IS_UNSET);
	return (NOT_BUILTIN);
}


// TODO: add shell as parameter, for some builtins
int handle_builtin(t_cmd command)
{
	t_builtin_type type;
	t_shell *shell;

	shell = (t_shell *)command.shell;
	type = get_builtin_type(command);
	if (type == IS_CD)
	{
            	handle_cd(command.arg, shell);
//		ft_printf("cd builtin\n");
		return (0);
	}
	if (type == IS_ECHO)
	{
		handle_echo(command.arg, shell);
	//	ft_printf("echo builtin\n");
		return (0);
	}
	if (type == IS_PWD)
	{
            	handle_pwd(shell);
		//ft_printf("pwd builtin\n");
		return (0);
	}
	if (type == IS_EXIT)
	{
            	handle_exit(shell, command.arg);
//		ft_printf("exit builtin\n");
		return (0);
	}
	if (type == IS_EXPORT)
	{
		ft_printf("export builtin\n");
		return (0);
	}
	if (type == IS_UNSET)
	{
            	handle_unset(shell, command.arg[0]);
		//ft_printf("unset builtin\n");
		return (0);
	}
	if (type == IS_ENV)
	{
           	handle_env(shell->envp); // Pass environment variables
		//ft_printf("env builtin\n");
		return (0);
	}
	return (1);
}

void	in_child(t_pipex pipex)
{
	t_cmd	command;
	int	file_red_result;

	if (pipex.command_count > 1)
		redirect_fds(&pipex);
	file_red_result = process_file_redirections(pipex.command + pipex.current_command);
	if (file_red_result)
	{
	// clean up
		exit(1);
	}
	if (!pipex.command[pipex.current_command].cmd_name)
	{
//TODO: clean up and exit success
		exit(0);
	}
	// TODO: only do if not builtin?
	if (get_builtin_type(command))
	{
		file_red_result = handle_builtin(command);
/*
		cleanup
*/
		exit(file_red_result);
	}
	else
	{
		get_command(&pipex);
		command = pipex.command[pipex.current_command];
		execve(command.path, command.argv, command.env);
		if (errno == ENOENT)
			error_and_exit(&pipex, CMD_FILE_NOT_FOUND);
		error_and_exit(&pipex, EXECVE_FAIL);
	}
}

int	after_fork(pid_t fork_result, t_pipex *pipex)
{
	if (fork_result == -1)
	{
		wait_all(*pipex);
		error_and_exit(pipex, FORK_FAIL);
	}
	if (fork_result == 0)
		in_child(*pipex);
	else if (pipex->current_command != pipex->command_count - 1)
		ft_close(&(pipex->pipe[1]));
	return (0);
}

int	wait_all(t_pipex pipex)
{
	int	wstatus;
	int	exit_status;

	wstatus = 0;
	exit_status = EXIT_FAILURE;
//TODO: consider using waitpid,	double check the intended behaviour
//TODO: check wait return -1
	while (pipex.current_command--)
	{
		if (wait(&wstatus) == pipex.last_pid)
		{
			if (WIFEXITED(wstatus))
				exit_status = WEXITSTATUS(wstatus);
			else if (WIFSIGNALED(wstatus))
				exit_status = 128 + WTERMSIG(wstatus);
		}
	}
	return (exit_status);
}
