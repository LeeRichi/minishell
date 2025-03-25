/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:45:10 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/25 14:24:29 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// //nn == new_node
// // d = delimeter
// //atkv_helper == arr_to_key_value_helper
// static void	atkv_helper(t_shell *shell, char *d, t_key_value *nn, int i)
// {
// 	*d = '\0';
// 	nn->key = ft_strdup(shell->envp[i]);
// 	if (!nn->key)
// 		malloc_fail_clean_exit(shell);
// 	nn->value = ft_strdup(d + 1);
// 	if (!nn->value)
// 		malloc_fail_clean_exit(shell);
// 	*d = '=';
// }

// t_key_value	*arr_to_key_value(t_shell *shell)
// {
// 	t_key_value	*head;
// 	t_key_value	*new_node;
// 	char		*delimiter;
// 	int			i;

// 	i = 0;
// 	head = NULL;
// 	while (shell->envp[i])
// 	{
// 		new_node = malloc(sizeof(t_key_value));
// 		if (!new_node)
// 			malloc_fail_clean_exit(shell);
// 		delimiter = ft_strchr(shell->envp[i], '=');
// 		if (delimiter)
// 			arr_to_key_value_helper(shell, delimiter, new_node, i);
// 		new_node->next = head;
// 		head = new_node;
// 		i++;
// 	}
// 	return (head);
// }

// void	free_key_value_list(t_key_value *head)
// {
// 	t_key_value	*temp;

// 	while (head)
// 	{
// 		temp = head;
// 		head = head->next;
// 		free(temp->key);
// 		free(temp->value);
// 		free(temp);
// 	}
// }

// static int	count_pairs(t_shell *shell)
// {
// 	t_key_value	*temp;
// 	int			count;

// 	count = 0;
// 	temp = shell->envp_value_pair;
// 	while (temp)
// 	{
// 		count++;
// 		temp = temp->next;
// 	}
// 	return (count);
// }

// void	from_pair_to_arr(t_shell *shell)
// {
// 	t_key_value	*temp;
// 	int			count;
// 	int			i;
// 	char		*temp_str;

// 	count = count_pairs(shell);
// 	clear_tokens(shell);
// 	shell->envp = malloc((count + 1) * sizeof(char *));
// 	if (!shell->envp)
// 		malloc_fail_clean_exit(shell);
// 	temp = shell->envp_value_pair;
// 	i = 0;
// 	while (temp)
// 	{
// 		shell->envp[i] = ft_strjoin(temp->key, "=");
// 		temp_str = shell->envp[i];
// 		shell->envp[i] = ft_strjoin(shell->envp[i], temp->value);
// 		free(temp_str);
// 		temp = temp->next;
// 		i++;
// 	}
// 	shell->envp[count] = NULL;
// 	free_key_value_list(shell->envp_value_pair);
// }

void	add_or_update_value_in_env(t_shell *shell, char *key, char *value)
{
	t_key_value	*temp;
	t_key_value	*new_node;

	shell->envp_value_pair = arr_to_key_value(shell);
	temp = shell->envp_value_pair;
	while (temp)
	{
		if (strcmp(temp->key, key) == 0)
		{
			if (temp->value)
				free(temp->value);
			temp->value = ft_strdup(value);
			from_pair_to_arr(shell);
			return ;
		}
		temp = temp->next;
	}
	new_node = malloc(sizeof(t_key_value));
	if (!new_node)
		malloc_fail_clean_exit(shell);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = shell->envp_value_pair;
	shell->envp_value_pair = new_node;
	from_pair_to_arr(shell);
}

static int	arg_name_checker(char *str)
{
	int	i;

	if ((str[0] >= '0' && str[0] <= '9') || !str[0])
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '@' || str[i] == '#' || str[i] == '&' || str[i] == '-')
			return (0);
		i++;
	}
	return (1);
}

static int	not_valid_id_print(t_shell *shell)
{
	ft_printf_fd(STDERR, " not a valid identifier\n");
	shell->exit_code = 1;
	return (1);
}

static int	equal_found(t_shell *shell, char *equal_pos, char **args, int i)
{
	*equal_pos = '\0';
	if (!arg_name_checker(args[i]))
		return (not_valid_id_print(shell));
	if (equal_pos[1] != '\0')
		add_or_update_value_in_env(shell, args[i], equal_pos + 1);
	else
		add_or_update_value_in_env(shell, args[i], "");
	return (0);
}

int	handle_export(t_shell *shell, char **args)
{
	int			i;
	t_key_value	*head;
	char		*equal_pos;

	head = NULL;
	i = 0;
	if (!args)
		return (0);
	while (args[i])
	{
		equal_pos = ft_strchr(args[i], '=');
		if (equal_pos)
		{
			if (equal_found(shell, equal_pos, args, i))
				return (1);
		}
		else
		{
			if (!arg_name_checker(args[i]))
				return (not_valid_id_print(shell));
		}
		i++;
	}
	free_key_value_list(head);
	return (0);
}
