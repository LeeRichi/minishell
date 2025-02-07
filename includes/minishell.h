/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:53:11 by chlee2            #+#    #+#             */
/*   Updated: 2025/02/07 17:54:52 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"

# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <stdio.h>
# include <signal.h>
# include <stdlib.h>

//defines
# define STDERR 2

# define SUCCESS 0
# define ERROR 1
# define NONE_NUMERIC_EXIT_CODE 255
# define WHITESPACE " \t\n"

typedef struct s_sig
{
	int sigint;
  	int sigquit;
}	t_sig;

typedef enum e_token_type {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT
} t_token_type;

typedef enum e_redirect_type {
    INPUT_REDIRECT,
    OUTPUT_REDIRECT,
    APPEND_REDIRECT,
    HERE_DOC
} t_redirect_type;

typedef struct s_redirection {
	t_redirect_type type;
	char	*file;
} t_redirection;

typedef struct s_cmd
{
	char		*cmd_name; //programm name
	char		**arg; //arguments of command
	t_redirect_type	*type;
	char		**infiles;
	char		**outfiles;
	int		pipe; //  pipe at the end
	int		redirection_index; // parsing purposes
	char	*path;		// execve
	char	**argv;		// execve
	char	**env;		// execve
// used for handling of "     " case
 	char	*input_arg;
	struct s_cmd		*next;
} t_cmd;

typedef struct s_pipex {
	pid_t		last_pid;
	size_t		command_count;
	size_t		current_command;
	int			pipe[2];
	int			reserve_fd;
	char		**env;				//is it ever adjusted through child process
	char		**first_command;		//rethink, unnecessary?
//	t_cmd		*parsed_cmds;
	t_cmd		*command;			//change type and adjust
	char		**path_split;			//rethink, should it happen in child?
}	t_pipex;

typedef struct s_shell
{
	char	**envp;
	char	*input;
	int		current_index;
	int 		exit_code;
	char	**tokens;
	int		token_count;
	int		in_single_quote;
	int		in_double_quote;
	int		err_code;
	t_token_type	last_token_type;
	t_cmd		*cmds;
} t_shell;


/* PIPEX */
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

int	pipex_launch(t_cmd *argv, char **env);
t_cmd	*free_command_content(t_cmd *command);
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
//void		get_command(char **argv, t_pipex *pipex);
void		get_command(t_pipex *pipex);
//t_pipex		get_pipex(int argc, char **argv, char **envp);
t_pipex		get_pipex(size_t argc, t_cmd *argv, char **envp);
void		print_current_error(void);
void		free_all(t_pipex pipex);
int			after_fork(pid_t fork_result, t_pipex *pipex);
int			wait_all(t_pipex pipex);
char		*get_command_path(char *filename, char **paths);
char		**get_path_split(char **envp, size_t ind);
//char		**get_command_argv(char *arg);
char		**get_command_argv(t_cmd cmd);
/* PIPEX END */


//global functions
void parse(t_shell *shell);

//sig.c
void handle_sigint(int code);
void handle_sigquit(int code);
void init_sig(void);

//builtins
void handle_echo(char **tokens);
void handle_cd(char **tokens);
int handle_pwd(void);
void handle_exit(t_shell *shell, char **tokens);

//lex
void tokenize_input(char *input, t_shell *shell);
int empty_between_checker(t_shell *shell);
char *str_append(char *str, char c);
//lex/wrong_pipe.c
int empty_pipe_checker(char *input, t_shell *shell);
void handle_wrong_pipes(t_shell *shell, char **current_token, int *token_count, char c);
//lex/wrong_quotes.c
char *handle_dollar_sign(char *s, int *index);
bool check_balanced_quotes(const char *input);
void handle_unbalanced_quotes(char **input);

//lex/lex_helper.c
char *str_append(char *str, char c);
char *get_env_value(const char *env_name);
int ft_arraylen(char **tokens);
int ft_start_with(char *str, char c);
char *ft_start_with_specials(char *str);
int ft_end_with(char *str, char c);

//utils
//free.c
void free_tokens(char **tokens);
void clear_tokens(t_shell *shell);
void ft_free_all(t_shell *shell);
void clear_cmds(t_shell *shell);
// print.c
void print_tokens(char **tokens);
void print_cmd_struct(t_cmd *cmd); // PRINT ALL CMD

//lex/heredoc.c
char *extract_delimiter(char *input, int *i);
void handle_heredoc(t_shell *shell, char *delimiter);

//structlize.c
void ft_structlize(t_shell *shell);

extern t_sig g_sig;
#endif
