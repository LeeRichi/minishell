/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 23:22:51 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/25 15:45:44 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "pipex.h"
//#include "minishell.h"
#include "../../includes/minishell.h"
/*
static void err_and_exit(char *fname, int line, t_pipex *pipex, t_error error)
{
	printf("%s, %d", fname, line);
	error_and_exit(pipex, error);
}
#define error_and_exit(x, y) err_and_exit(__FILE__, __LINE__, x, y)
*/
/*
TODO: set

adapt to t_cmd:
	remove some pieces from t_pipex, as they already exist in t_cmd
	
	rewrite get pipex:
	


*/
// TODO: replace argv with t_cmd * list

int	t_cmd_list_count(t_cmd *head)
{
	int	counter;

	counter = 0;
	while(head)
	{
		counter++;
		head = head->next;
	}
	return (counter);
}

//int	pipex_launch(int command_count, char **argv, char **env)
//TODO: add ambigous redir message here???!!!
int	pipex_launch(t_cmd *cmds, char **env, t_shell *shell)
{
	t_pipex	pipex;
	pid_t	pid;
	int		wait_all_return;
	int command_count;

	command_count = t_cmd_list_count(cmds);
	shell->pipex = 0;
	pipex = get_pipex(command_count, cmds, env, shell);
	if (!pipex.command)
	{
		//TODO: handle malloc fail error
		perror("pipex alloc fail");
		//TODO: malloc_fail_clean_exit
		return 0; ///asdassdas
	}
	shell->pipex = &pipex;
	if (!resolve_heredoc_cmds(pipex.command, command_count))
	{
		if (shell->err_code)
		{
			shell->err_code = 0;
			shell->pipex = 0;
			return shell->exit_code;
		}
		else
		{
			error_and_exit(&pipex, error_init(HEREDOC_FAIL, 0, 0));
		}
	}
	before_child_process_signal();
	while (pipex.current_command < pipex.command_count)
	{
		before_fork(&pipex);
		pid = fork();
		if (pid != -1)
			pipex.last_pid = pid;
		after_fork(pid, &pipex);
		pipex.current_command++;
	}
	ft_close(&pipex.pipe[0]);
	ft_close(&pipex.pipe[1]);
	wait_all_return = wait_all(pipex);
	set_minishell_signal();
	free_pipex(pipex);
	shell->pipex = 0;
	return (wait_all_return);
}
