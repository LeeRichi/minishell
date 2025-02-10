/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:53:11 by chlee2            #+#    #+#             */
/*   Updated: 2025/02/10 18:58:30 by chlee2           ###   ########.fr       */
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

//printing purpose
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"
#define GREEN "\033[32m"

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

typedef struct s_cmd
{
    char            *cmd_name;
	char 			**arg;
	t_redirect_type redirect_type[10]; //fix later 
    // t_redirect_type *redirect_type;
	char		    **infiles;
	char		    **outfiles;
    struct s_cmd    *next;
    int             pipe; //flag, 1 means there's a pipe following up
    int redirection_index; //example, echo hello > out.txt >> out2.txt < in.txt, > has redirection_index of 0, >> has 1, so on.
    int ambiguous_flag_node;
} t_cmd;

typedef struct s_shell
{
    char	**envp;
    char    *input;
	int 	current_index;
	int 	exit_code;
	char    **tokens;
	int		token_count;
	int		in_single_quote;
    int		in_double_quote;
	int 	err_code;
    int     ambiguous_flag;

	t_token_type    last_token_type;
    t_cmd   *cmds;
} t_shell;


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
char *ft_start_with_specials_v2(char *str);
char *str_append(char *str, char c);
//lex/wrong_pipe.c
int empty_pipe_checker(char *input, t_shell *shell);
void handle_wrong_pipes(t_shell *shell, char **current_token, int *token_count, char c);
//lex/wrong_quotes.c
char *handle_dollar_sign(t_shell *shell, char *s, int *index);
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
void free_matrix(char **matrix);
// print.c
void print_tokens(char **tokens);
void print_cmd_struct(t_cmd *cmd);

//lex/heredoc.c
char *extract_delimiter(char *input, int *i);
void handle_heredoc(t_shell *shell, char *delimiter);

//structlize.c
void ft_structlize(t_shell *shell);

//exit.c
int ft_isNum(char *s);

extern t_sig g_sig;
#endif
