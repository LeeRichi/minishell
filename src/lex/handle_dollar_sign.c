/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:25:01 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/10 18:52:02 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_c_num(char c)
{
	if (c >= '1' && c <= '9')
		return (1);
	return (0);
}

static char	*extract_env_name(t_shell *shell, char *s, int *index, char **temp)
{
	int		len;
	char	*result;

	(void)shell;
	len = 0;
	(*index)++;
	if (is_c_num(s[*index]))
	{
		(*index)++;
		*temp = s + *index;
	}
	while (ft_isalnum(s[*index]) || s[*index] == '_')
	{
		len++;
		(*index)++;
	}
	result = malloc(len + 1);
	if (!result)
		return (0);
	(*index) -= len;
	ft_memcpy(result, s + *index, len);
	*index += len;
	(*index)--;
	result[len] = '\0';
	//printf("extr env name: %s\b", result);
	return (result);
}

bool	check_balanced_quotes(const char *input)
{
	int	single_quotes;
	int	double_quotes;
	int	i;

	single_quotes = 0;
	double_quotes = 0;
	i = 0;
	if (!input)
		return (false);
	while (input[i] != '\0')
	{
		if (input[i] == '\\')
			i++;
		else if (input[i] == '\'' && double_quotes % 2 == 0)
			single_quotes++;
		else if (input[i] == '"' && single_quotes % 2 == 0)
			double_quotes++;
		if (!input[i])
			break ;
		i++;
	}
	return (single_quotes % 2 == 0 && double_quotes % 2 == 0);
}

void	handle_unbalanced_quotes(t_shell *shell, char **input)
{
	char	*new_input;
	char	*additional_input;

	while (!check_balanced_quotes(*input))
	{
		additional_input = readline("> ");
		if (!additional_input)
		{
			ft_printf_fd(STDERR, "minishell: EOF while waiting for quotes\n");
			// TODO: add syntax error message
			ft_printf_fd(STDERR, "minishell: syntax error\n");
			// free(*input);
			shell->err_code = 2;
			// clear_tokens(shell);
			break ;
			// free_matrix(shell->envp);
			
			// exit(EXIT_FAILURE);
			//mark
		}
		new_input = ft_strjoin(*input, additional_input);
		if (!new_input)
		{
			free(*input);
			free(additional_input);
			malloc_fail_clean_exit(shell);
		}
		free(*input);
		free(additional_input);
		*input = new_input;
	}
}

char	*handle_dollar_sign(t_shell *shell, char *s, int *index, char *ct)
{
	char	*env_name;
	char	*result;
	char	*temp;

	temp = NULL;
	env_name = extract_env_name(shell, s, index, &temp);
	if (!env_name)
	{
		if (ct)
			free(ct);
		malloc_fail_clean_exit_v2(shell, s);
	}
	result = get_env_value(env_name, shell);
	free(env_name);
	if (!result)
	{
		if (temp)
			return (temp);
		return (NULL);
	}
	return (result);
}
