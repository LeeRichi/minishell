/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:24:18 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/25 14:27:21 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//nn == new_node
// d = delimeter
//atkv_helper == arr_to_key_value_helper
static void	atkv_helper(t_shell *shell, char *d, t_key_value *nn, int i)
{
	*d = '\0';
	nn->key = ft_strdup(shell->envp[i]);
	if (!nn->key)
		malloc_fail_clean_exit(shell);
	nn->value = ft_strdup(d + 1);
	if (!nn->value)
		malloc_fail_clean_exit(shell);
	*d = '=';
}

t_key_value	*arr_to_key_value(t_shell *shell)
{
	t_key_value	*head;
	t_key_value	*new_node;
	char		*delimiter;
	int			i;

	i = 0;
	head = NULL;
	while (shell->envp[i])
	{
		new_node = malloc(sizeof(t_key_value));
		if (!new_node)
			malloc_fail_clean_exit(shell);
		delimiter = ft_strchr(shell->envp[i], '=');
		if (delimiter)
			atkv_helper(shell, delimiter, new_node, i);
		new_node->next = head;
		head = new_node;
		i++;
	}
	return (head);
}

void	free_key_value_list(t_key_value *head)
{
	t_key_value	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

static int	count_pairs(t_shell *shell)
{
	t_key_value	*temp;
	int			count;

	count = 0;
	temp = shell->envp_value_pair;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

void	from_pair_to_arr(t_shell *shell)
{
	t_key_value	*temp;
	int			count;
	int			i;
	char		*temp_str;

	count = count_pairs(shell);
	clear_tokens(shell);
	shell->envp = malloc((count + 1) * sizeof(char *));
	if (!shell->envp)
		malloc_fail_clean_exit(shell);
	temp = shell->envp_value_pair;
	i = 0;
	while (temp)
	{
		shell->envp[i] = ft_strjoin(temp->key, "=");
		temp_str = shell->envp[i];
		shell->envp[i] = ft_strjoin(shell->envp[i], temp->value);
		free(temp_str);
		temp = temp->next;
		i++;
	}
	shell->envp[count] = NULL;
	free_key_value_list(shell->envp_value_pair);
}
