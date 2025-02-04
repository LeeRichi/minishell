/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:32:51 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/02/04 15:47:22 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "libft.h"

typedef struct s_command {
	char	*path;
	char	**argv;
	char	**env;
	char	*input_arg;
}	t_command;

typedef struct s_pipex {
	pid_t		last_pid;
	size_t		command_count;
	size_t		current_command;
	char		*infile;			//remove
	char		*outfile;			//remove
	int			pipe[2];
	int			reserve_fd;
	char		**env;				//is it ever adjusted through child process
	char		**first_command;		//rethink
	t_command	*command;			//change type and adjust
	char		**path_split;			//rethink
}	t_pipex;

typedef enum e_perrtypes {
	MALLOC_FAIL,
	CMD_NOT_FOUND,
	CMD_FILE_NOT_FOUND,
	PROG_FILE_IS_DIR,
	FILE_NOT_FOUND,
	DUP_FAIL,
	RFILE_FAIL,
	WFILE_FAIL,
	OPEN_FAIL,
	PERMISSION_FAIL,
	EXECVE_FAIL,
	PIPE_FAIL,
	FORK_FAIL
}	t_perrtypes;

t_command	*free_command_content(t_command *command);
void		error_and_exit(t_pipex *pipex, t_perrtypes errtype);
void		ft_close(int *fd);
int			dup2_and_close(int *fd_from, int fd_to);
void		free_split(char **args);
int			check_exists_and_not_dir(char *path);
int			count_split(char **texts);
int			process_rfile_name_arg(t_pipex *pipex);
int			process_wfile_name_arg(t_pipex *pipex);
void		redirect_fds(t_pipex *pipex);
void		before_fork(t_pipex *pipex);
void		get_command(char **argv, t_pipex *pipex);
t_pipex		get_pipex(int argc, char **argv, char **envp);
void		print_current_error(void);
void		free_all(t_pipex pipex);
int			after_fork(pid_t fork_result, t_pipex *pipex);
int			wait_all(t_pipex pipex);
char		*get_command_path(char *filename, char **paths);
char		**get_path_split(char **envp, size_t ind);
char		**get_command_argv(char *arg);

#endif
