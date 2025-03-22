// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parse_input_character.c                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/03/22 15:44:31 by chlee2            #+#    #+#             */
// /*   Updated: 2025/03/22 16:47:10 by chlee2           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// void	handle_empty_token_strdup(t_shell *shell, char **current_token,  int *i)
// {	
// 	if (*current_token == NULL)
// 	{
// 		*current_token = ft_strdup("");
// 		if (*current_token == NULL)
// 			malloc_fail_clean_exit(shell);
// 	}
// 	(*i)++;
// }

// void	handle_wave_helper(t_shell *shell, char **ct, int *i, char *input)
// {
// 	int		j;
// 	char	*home_dir;

// 	home_dir = ft_getenv("HOME", shell);
// 	if (home_dir != NULL)
// 	{
// 		j = 0;
// 		while (home_dir[j++])
// 			*ct = str_append(shell, *ct, home_dir[j - 1]);
// 		free(home_dir);
// 	}
// 	if (input[*i] == '/')
// 	{
// 		while (input[*i] != ' ' && input[*i])
// 		{
// 			*ct = str_append(shell, *ct, input[*i]);
// 			(*i)++;
// 		}
// 	}
// 	return ;
// }

// void	handle_wave(t_shell *shell, char **ct, int *i, char *input)
// {
// 	// int	j;

// 	if (input[*i + 1] == '|' || input[*i + 1] == '\0'
// 		|| input[*i + 1] == ' ' || input[*i + 1] == '/')
// 		handle_wave_helper(shell, ct, i, input);
// 	while (input[*i] == '~')
// 	{
// 		*ct = str_append(shell, *ct, '~');
// 		(*i)++;
// 	}
// 	*ct = str_append(shell, *ct, input[*i]);
// }

// void	white_space_found_no_quote(t_shell *shell, char **ct, int *i, char *s)
// {
// 	finalize_token(shell, ct, &shell->token_count);
// 	if (s[*i - 1] == '|')
// 		shell->last_token_type = 1;
// 	else if (s[*i - 1] == '>' || s[*i - 1] == '<')
// 		shell->last_token_type = 2;
// 	else
// 		shell->last_token_type = 0;
// }

// void	handle_consecutive_redir(t_shell *shell, char **ct, int *i, char *input)
// {
// 	if (input[*i + 1] != '\0' && input[*i + 1] == '>')
// 	{
// 		*ct = str_append(shell, *ct, input[*i]);
// 		*ct = str_append(shell, *ct, input[*i + 1]);
// 		(*i)++;
// 	}
// 	else
// 		*ct = str_append(shell, *ct, input[*i]);
// 	finalize_token(shell, ct, &shell->token_count);
// }

// //TODO: check all mallocs and free and exit if the do
// void	parse_input_character(t_shell *shell, char **ct, int *i, char *s)
// {
// 	if ((s[*i] == '"' && s[*i + 1] == '"')
// 		|| (s[*i] == '\'' && s[*i + 1] == '\''))
// 		handle_empty_token_strdup(shell, ct, i);
// 	else if (s[*i] == '\'' && !(shell->in_double_quote))
// 		handle_single_quote(shell, ct, i, s);
// 	else if (s[*i] == '"' && !(shell->in_single_quote))
// 		handle_double_quote(shell, ct, i, s);
// 	else if (s[*i] == '~' && !(shell->in_single_quote)
// 		&& !(shell->in_double_quote))
// 		handle_wave(shell, ct, i, s);
// 	else if (!(shell->in_single_quote) && s[*i] == '$' && s[*i + 1] != '\0')
// 		massive_dollar_sign_handler(shell, ct, i, s);
// 	else if (strchr(WHITESPACE, s[*i])
// 		&& !(shell->in_single_quote) && !(shell->in_double_quote))
// 		white_space_found_no_quote(shell, ct, i, s);
// 	else if (s[*i] == '>' || s[*i] == '<')
// 		handle_consecutive_redir(shell, ct, i, s);
// 	else
// 		*ct = str_append(shell, *ct, s[*i]);
// }
