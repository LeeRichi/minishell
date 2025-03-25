/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:28:08 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/25 15:36:11 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "pipex.h"
//#include "minishell.h"
#include "../../includes/minishell.h"
/*
static void err_and_exit(char *fname, int line, t_pipex *pipex, t_perrtypes errtype)
{
	printf("%s, %d", fname, line);
	error_and_exit(pipex, errtype);
}
#define error_and_exit(x, y) err_and_exit(__FILE__, __LINE__, x, y)
*/
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

int handle_builtin(t_cmd command)
{
	t_builtin_type type;
	t_shell *shell;

	shell = (t_shell *)command.shell;
	
	type = get_builtin_type(command);
	if (type == IS_CD)
	{
		return (handle_cd(command.arg, shell));
	}
	if (type == IS_ECHO)
	{
		return (handle_echo(command.arg, shell));
	}
	if (type == IS_PWD)
	{
		return handle_pwd(shell);
	}
	if (type == IS_EXIT)
	{
		return handle_exit(shell, command.arg);
	}
	if (type == IS_EXPORT)
	{
		return handle_export(shell, command.arg);
	}
	if (type == IS_UNSET)
	{
 		return handle_unset(shell);
	}
	if (type == IS_ENV)
	{
		return handle_env(shell->envp);
	}
	return (1);
}
/*
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
	get_command(&pipex);
	command = pipex.command[pipex.current_command];
	if (get_builtin_type(command))
	{
		file_red_result = handle_builtin(command);

		cleanup
		exit(file_red_result);
	}
	else
	{
	//	printf("test printf: %s , %s, %s, %s END\n", command.argv[0], command.argv[1], command.argv[2],command.argv[3]  );
		execve(command.path, command.argv, command.env);
		if (errno == ENOENT)
			error_and_exit(&pipex, CMD_FILE_NOT_FOUND);
		error_and_exit(&pipex, EXECVE_FAIL);
	}
}
*/
void	in_child(t_pipex *pipex)
{
	t_cmd	command;
	int	file_red_result;
	t_shell	*shell;

	set_child_signal();
	shell = (t_shell *)pipex->shell;
	if (pipex->command_count > 1)
		redirect_fds(pipex);
	file_red_result = process_file_redirections(pipex->command + pipex->current_command);
	if (file_red_result)
	{
		ft_free_all(shell);
		exit(1);
	}
	if (!pipex->command[pipex->current_command].cmd_name)
	{
		ft_free_all(shell);
		exit(0);
	}
	if (get_builtin_type(pipex->command[pipex->current_command]))
	{
		file_red_result = handle_builtin(pipex->command[pipex->current_command]);
		ft_free_all(shell);
		exit(file_red_result);
	}
	else
	{
		get_command(pipex);
		command = pipex->command[pipex->current_command];
		execve(command.path, command.argv, command.env);
		if (errno == ENOENT)
			error_and_exit(pipex, error_init(CMD_FILE_NOT_FOUND, 0, command.argv[0]));
		//perror(command.path);
		error_and_exit(pipex, error_init(EXECVE_FAIL, 0, command.argv[0]));
	}
}

int	after_fork(pid_t fork_result, t_pipex *pipex)
{
	if (fork_result == -1)
	{
		wait_all(*pipex);
		error_and_exit(pipex, error_init(FORK_FAIL, 0, 0));
	}
	if (fork_result == 0)
		in_child(pipex);
	else if (pipex->current_command != pipex->command_count - 1)
		ft_close(&(pipex->pipe[1]));
	return (0);
}

// TODO: use alt_wait_all in place of wait?
/*
int	alt_wait_all(int pid)
{
	int	wait_status;
	int	wait_return;
	int	exit_status;

	wait_status = 0;
	exit_status = EXIT_FAILURE;
	while (1)
	{
		wait_return = wait(&wait_status);
		if (wait_return == -1)
			break ;
		if (wait_return == pid)
		{
			if (WIFEXITED(wait_status))
				exit_status = WEXITSTATUS(wait_status);
			else if (WIFSIGNALED(wait_status))
				exit_status = 128 + WTERMSIG(wait_status);
		}
	}
	return (exit_status);
}
*/
int	wait_all(t_pipex pipex)
{
	int	wstatus;
	int	exit_status;
	int	sig_int_child;
	int	exit_status_tmp;
	int	wait_res;

	sig_int_child = 0;
	wstatus = 0;
	exit_status = EXIT_FAILURE;
//TODO: consider using waitpid,	double check the intended behaviour
//TODO: check wait return -1
	while (pipex.current_command--)
	{
		wait_res = wait(&wstatus);
		if (wait_res == -1)
			break;
		if (wait_res == pipex.last_pid)
		{
			if (WIFEXITED(wstatus))
				exit_status = WEXITSTATUS(wstatus);
			else if (WIFSIGNALED(wstatus))
				exit_status = 128 + WTERMSIG(wstatus);
			if (exit_status == 130)
				sig_int_child = 1;
			if (exit_status == 131)
				ft_putstr_fd("Quit (Core dumped)\n", 2);
		}
		else
		{
			if (WIFEXITED(wstatus))
				exit_status_tmp = WEXITSTATUS(wstatus);
			else if (WIFSIGNALED(wstatus))
				exit_status_tmp = 128 + WTERMSIG(wstatus);
			if (exit_status_tmp == 130)
				sig_int_child = 1;
		}
	}
	if (sig_int_child)
		ft_putstr_fd("\n", 2);
	return (exit_status);
}
