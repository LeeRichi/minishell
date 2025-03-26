/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:45:10 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/26 14:26:41 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_or_update_value_in_env(t_shell *shell, char *key, char *value)
{
	t_key_value	*temp;
	t_key_value	*new_node;

	shell->envp_value_pair = arr_to_key_value(shell);
	temp = shell->envp_value_pair;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
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
