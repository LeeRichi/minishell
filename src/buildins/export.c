/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:45:10 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/30 21:04:28 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	arg_name_checker(char *str)
{
	int	i;

	if ((str[0] >= '0' && str[0] <= '9') || !str[0] ||  str[0]=='=')
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

int	exist_as_var(char *str, char *envp_member)
{
	char *eq_position;
	int	length_of_key;
	
	length_of_key = 0;
	eq_position = ft_strchr(str, '=');
	if (eq_position)
		length_of_key =  eq_position - str;
	else
		length_of_key = ft_strlen(str);
	if (!length_of_key)
		return (0);
	if (ft_strncmp(str, envp_member, length_of_key) != 0)
		return 0;
	if (*(str + length_of_key) == '=' || *(str + length_of_key) == 0 )
		return (1);
	return (0);
}

int	get_envp_var_index(char *str, t_shell *shell)
{
	char	**envp;
	int		index;

	envp = shell->envp;
	if (!envp)
		return (-1);
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

int	adjust_envp(char *str, t_shell *shell, int envp_index)
{
	char	*new_envp_member;
	char	**temp;
	int		envp_length;

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
	int			var_index;

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
