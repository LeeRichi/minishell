/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:28:08 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/04/04 19:01:22 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_builtin_type	get_builtin_type(t_cmd cmd)
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

int	handle_builtin(t_cmd command)
{
	t_builtin_type	type;
	t_shell			*shell;

	shell = (t_shell *)command.shell;
	type = get_builtin_type(command);
	if (type == IS_CD)
		return (handle_cd(command.arg, shell));
	if (type == IS_ECHO)
		return (handle_echo(command.arg, shell));
	if (type == IS_PWD)
		return (handle_pwd(shell));
	if (type == IS_EXIT)
		return (handle_exit(shell, command.arg));
	if (type == IS_EXPORT)
		return (handle_export(shell, command.arg));
	if (type == IS_UNSET)
		return (handle_unset(shell));
	if (type == IS_ENV)
		return (handle_env(shell->envp));
	return (1);
}

void	ft_free_and_exit(t_shell *shell, int exit_code)
{
	ft_free_all(shell);
	exit(exit_code);
}

void	in_child(t_pipex *pipex)
{
	t_cmd	*command;
	int		file_red_result;
	t_shell	*shell;

	command = pipex->command + pipex->current_command;
	if (set_child_signal())
		error_and_exit(pipex, error_init(SIG_FAIL, 0, 0));
	shell = (t_shell *)pipex->shell;
	if (pipex->command_count > 1)
		redirect_fds(pipex);
	file_red_result = process_file_redirections(command);
	in_child_free_and_exit(shell, file_red_result, command);
	if (get_builtin_type(*command))
		ft_free_and_exit(shell, handle_builtin(*command));
	else
	{
		get_command(pipex);
		execve(command->path, command->argv, command->env);
		if (errno == ENOENT)
			error_and_exit(pipex, error_init(CMD_FILE_NOT_FOUND,
					0, command->argv[0]));
		error_and_exit(pipex, error_init(EXECVE_FAIL, 0, command->argv[0]));
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
