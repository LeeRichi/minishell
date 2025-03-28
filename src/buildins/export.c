/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:45:10 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/29 18:05:21 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


// envp KEY=

/*
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
*/
// TODO: case "asd =wasd"
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

//KEY=
//KEY=asdasdddas

//KEY=
//KEY=asdasdddas

//my=nameKEY
/*
static int	equal_found(t_shell *shell, char *equal_pos, char **args, int i)
{
	*equal_pos = '\0';
	//if (!arg_name_checker(args[i]))
	//	return (not_valid_id_print(shell));
	if (equal_pos[1] != '\0')
		add_or_update_value_in_env(shell, args[i], equal_pos + 1);
	else
		add_or_update_value_in_env(shell, args[i], "");
	return (0);
}
*/
int exist_as_var(char *str, char *envp_member)
{
	char *eq_position;
	int	length_of_key;
	
	length_of_key = 0;
	eq_position = ft_strchr(str, '=');
	if (eq_position)
		length_of_key =  eq_position - str;
	else
		length_of_key = ft_strlen(str);
	if (ft_strncmp(str, envp_member, length_of_key) != 0)
		return 0;
	if (*(str + length_of_key) == '=' || *(str + length_of_key) == 0 )
		return (1);
	return (0);
}

int get_envp_var_index(char *str, t_shell *shell)
{
	char **envp = shell->envp;
	int	index;

	index = 0;
	while(envp[index])
	{
		if (exist_as_var(str, envp[index]))
		{
			return (index);
		}
		index++;
	}
	return (-1);
}



/*static int	equal_found(t_shell *shell, char *equal_pos, char **args, int i)
{
	*equal_pos = '\0';
	//if (!arg_name_checker(args[i]))
	//	return (not_valid_id_print(shell));
	if (equal_pos[1] != '\0')
		add_or_update_value_in_env(shell, args[i], equal_pos + 1);
	else
		add_or_update_value_in_env(shell, args[i], "");
	return (0);
}
*/
int adjust_envp(char *str, t_shell *shell, int envp_index)
{
	char *new_envp_member;
	char **temp;
	int envp_length;

	envp_length = count_split(shell->envp);
	new_envp_member = ft_strdup(str);
	if (!new_envp_member)
		return (0);
	if (envp_index == -1)
	{
		temp = ft_calloc(envp_length + 2, sizeof(char *));
		if (!temp)
		{
			free(new_envp_member);
			return (0);
		}
		ft_memmove(temp, shell->envp, envp_length * sizeof(char *));
		temp[envp_length] = new_envp_member;
		free(shell->envp);
		shell->envp = temp;
	}
	else
	{
		free(shell->envp[envp_index]);
		shell->envp[envp_index] = new_envp_member;
	}
	return (1);
}



int	handle_export(t_shell *shell, char **args)
{
	int			i;
	t_key_value	*head;
	char		*equal_pos;
	int	var_index;
	head = NULL;
	i = 0;
	if (!args)
		return (0);
	while (args[i])
	{
		if (!arg_name_checker(args[i]))
				return (not_valid_id_print(shell));
		equal_pos = ft_strchr(args[i], '=');
		if (equal_pos)
		{
			var_index = get_envp_var_index(args[i], shell);
			if (!adjust_envp(args[i], shell, var_index))
				return (1);
		}
		i++;
	}
	return (0);
}

/*
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
*/