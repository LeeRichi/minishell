/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:53:11 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/25 21:22:10 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef SHELL_NAME
# define SHELL_NAME "wow"
# endif
# include "../lib/libft/libft.h"

# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <stdio.h>
# include <signal.h>
# include <stdlib.h>

//defines
#define STDIN  0   // Standard input
#define STDOUT 1   // Standard output
#define STDERR 2   // Standard error

# define SUCCESS 0
# define ERROR 1
# define NONE_NUMERIC_EXIT_CODE 255
# define WHITESPACE " \t\n"

#ifndef PATH_MAX
	#define PATH_MAX 4096
#endif

//printing purpose
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"
#define GREEN "\033[32m"
// TODO: change it back
typedef struct sigaction t_sigaction;
/*
typedef struct s_sig
{
	int sigint;
  	int sigquit;
}	t_sig;
*/
typedef enum e_token_type {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT,
	TOKEN_HEREDOC
} t_token_type;

typedef enum e_redirect_type {
    INPUT_REDIRECT,
    OUTPUT_REDIRECT,
    APPEND_REDIRECT,
    HERE_DOC
} t_redirect_type;

typedef enum e_builtin_type {
	NOT_BUILTIN = 0,
	IS_CD,
	IS_ECHO,
	IS_ENV,
	IS_EXIT,
	IS_EXPORT,
	IS_PWD,
	IS_UNSET
} t_builtin_type;

typedef struct s_redirection {
	t_redirect_type type;
	char	*file;
} t_redirection;

typedef struct s_key_value
{
    char *key;
    char *value;
    struct s_key_value *next;
} t_key_value;

typedef struct s_cmd
{
	char		*cmd_name; //programm name
	char		**arg; //arguments of command
	t_redirect_type	*redirect_type;  // Dynamic allocation
	char		**infiles;
	char		**outfiles;
	int		heredoc_fd;			//when close == -1, when open - legal fd, opening error handled in pipex
	int		pipe; //  pipe at the end
	int		redirection_index; // parsing purposes
	char	*path;		// execve
	char	**argv;		// execve
	char	**env;		// execve
	void	*shell;
  int ambiguous_flag_node; //USE THIS
	struct s_cmd		*next;
} t_cmd;

typedef struct s_pipex {
	pid_t		last_pid;
	size_t		command_count;
	size_t		current_command;
	int			pipe[2];
	int			reserve_fd;
	char		**env;				//is it ever adjusted through child process
	t_cmd		*command;			//change type and adjust
	char		**path_split;			//rethink, should it happen in child?
	void	*shell;
}	t_pipex;

typedef struct s_shell
{
	char	**envp;
	t_key_value *envp_value_pair;
	char *input;
	int		current_index;
	int 		exit_code;
	char	**tokens;
	int		token_count;
	int		in_single_quote;
	int		in_double_quote;
	int		err_code;
	t_token_type	last_token_type;
	t_cmd		*cmds;			// TODO: add pipex here for error handling, free up cmds linked list, use arr from pipex
	int		stdin_fd;
	int		stdout_fd;
	t_pipex		*pipex;
  int     ambiguous_flag;   //DEPRECATED
  pid_t shell_id;

  int has_quotes;
} t_shell;

/* PIPEX */
typedef enum e_perrtypes {
	MALLOC_FAIL,
	CMD_NOT_FOUND,
	CMD_FILE_NOT_FOUND,
	PROG_FILE_IS_DIR,
	FILE_NOT_FOUND,
	HEREDOC_FAIL,
	DUP_FAIL,
	RFILE_FAIL,
	WFILE_FAIL,
	APPEND_FAIL,
	OPEN_FAIL,
	PERMISSION_FAIL,
	EXECVE_FAIL,
	PIPE_FAIL,
	FORK_FAIL,
	FILE_REDIR_FAIL,
	AMBIGOUS_REDIR,
}	t_perrtypes;

typedef struct s_error
{
	char *f_name;
	char *cmd_name;
//	char *strerror_message;
//	char *final_message;
	t_perrtypes errtype;
} t_error;



char *get_redir_str(int index, t_cmd cmd);
int	pipex_launch(t_cmd *argv, char **env, t_shell *shell);
int check_heredoc(t_cmd cmd);
int get_cmd_heredoc(t_cmd cmd);
int get_here_doc_fd(char *eof, t_shell *shell);
t_cmd	*free_pipex_cmd(t_cmd *command);
size_t	count_files(t_cmd *cmd);
//void		error_and_exit(t_pipex *pipex, t_perrtypes errtype);
t_error error_init(t_perrtypes errtype, char *file_name, char *command_name);
void	print_error_message(t_error error);
void		error_and_exit(t_pipex *pipex, t_error error);
//void	error_and_exit(t_pipex *pipex, t_perrtypes errtype, t_error error);
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
t_pipex		get_pipex(size_t argc, t_cmd *argv, char **envp, t_shell *shell);
void		print_current_error(void);
void		free_pipex(t_pipex pipex);
int			after_fork(pid_t fork_result, t_pipex *pipex);
int			wait_all(t_pipex pipex);
char		*get_command_path(char *filename, char **paths);
char		**get_path_split(char **envp, size_t ind);
//char		**get_command_argv(char *arg);
char		**get_command_argv(t_cmd cmd);
char	*ft_split_join(char **tab, char *sep);
/* PIPEX END */


/*	processing	*/
void	execute(t_shell *shell);
int	resolve_heredoc_cmds(t_cmd *cmds, size_t command_count);
int	process_file_redirections(t_cmd *cmd);
int	handle_builtin(t_cmd command);
t_builtin_type get_builtin_type(t_cmd cmd);

//global functions
void parse(t_shell *shell);

//sig.c
//void handle_sigint(int code);
//void handle_sigquit(int code);
//void init_sig(void);
void set_minishell_signal(void);
void before_child_process_signal(void);
void set_child_signal(void);
void set_heredoc_signal(void);
void	before_heredoc_process_signal(void);

//builtins
int handle_echo(char **tokens, t_shell *shell);
int handle_cd(char **tokens, t_shell *shell);
int handle_pwd(t_shell *shell);
int handle_exit(t_shell *shell, char **args);
int handle_env(char **envp);
int handle_unset(t_shell *shell);
int handle_export(t_shell *shell, char **args);

//utils/lvl_handler.c
void shell_level_ctrl(t_shell *shell);

//lex
void tokenize_input(char *input, t_shell *shell);

//lex/parse_input_fragment.c
void finalize_token(t_shell *shell, char **current_token, int *token_count);

//lex/checkers.c
int empty_between_checker(t_shell *shell);
int empty_pipe_checker(char *input, t_shell *shell);
//lex/parse_input_character.c
void parse_input_character(t_shell *shell, char **current_token, int *i, char *input);
//lex/parse_input_character_page_2.c
void	handle_empty_token_strdup(t_shell *shell, char **current_token,  int *i);
//lex/parse_input_fragment.c
void parse_input_fragment(char *input, t_shell *shell);
//lex/massive_dollar_sign_handler.c
void massive_dollar_sign_handler(t_shell *shell, char **current_token, int *i, char *input);
//lex/handle_double_quote.c
void handle_double_quote(t_shell *shell, char **current_token, int *i, char *input);
//lex/handle_single_quote.c
void handle_single_quote(t_shell *shell, char **current_token, int *i, char *input);

//lex/wrong_pipe.c
void handle_wrong_pipes(t_shell *shell, char **current_token, int *token_count, char c);
//lex/handle_dollar_sign.c
bool check_balanced_quotes(const char *input);
void handle_unbalanced_quotes(t_shell *shell, char **input);
char *handle_dollar_sign(t_shell *shell, char *s, int *index);

//lex/lex_helper.c
char *str_append(t_shell *shell, char *str, char c);
char *get_env_value(char *env_name, t_shell *shell);
int ft_start_with(char *str, char c);
char *ft_start_with_specials(char *str);
int ft_end_with(char *str, char c);

void handle_consecutive_redir(t_shell *shell, char **current_token, int *i, char *input);

//utils
//free.c
void free_tokens(char **tokens);
void clear_tokens(t_shell *shell);
void ft_free_all(t_shell *shell);
void clear_cmds(t_shell *shell);
void free_matrix(char **matrix);
void malloc_fail_clean_exit(t_shell *shell);
// test_print.c
void print_tokens(char **tokens);
void print_cmd_struct(t_cmd *cmd); // PRINT ALL CMD

//lex/heredoc.c
char *extract_delimiter(char *input, int *i);
void handle_heredoc(t_shell *shell, char *delimiter);

//structlize.c
void ft_structlize(t_shell *shell);

// ft_getenv.c
char *ft_getenv(char *env_name, t_shell *shell);

//export.c
t_key_value *arr_to_key_value(t_shell *shell);
void free_key_value_list(t_key_value *head);

extern int g_sig;

#endif
