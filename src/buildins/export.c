/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:45:10 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/31 20:56:09 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	arg_name_checker(char *str)
{
	int	i;

	if ((str[0] >= '0' && str[0] <= '9') || !str[0] || str[0] == '=')
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '@' || str[i] == '#' || str[i] == '&'
			|| str[i] == '-' || str[i] == '+' || str[i] == '}'
			|| str[i] == '{' || str[i] == '.' || str[i] == '*'
			|| str[i] == '!' || str[i] == '^')
			return (0);
		i++;
	}
	return (1);
}

int	not_valid_id_print(t_shell *shell)
{
	ft_printf_fd(STDERR, " not a valid identifier\n");
	shell->exit_code = 1;
	return (1);
}

int	exist_as_var(char *str, char *envp_member)
{
	char	*eq_position;
	int		length_of_key;

	length_of_key = 0;
	eq_position = ft_strchr(str, '=');
	if (eq_position)
		length_of_key = eq_position - str;
	else
		length_of_key = ft_strlen(str);
	if (!length_of_key)
		return (0);
	if (ft_strncmp(str, envp_member, length_of_key) != 0)
		return (0);
	if (*(str + length_of_key) == '=' || *(str + length_of_key) == 0)
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
	while (envp[index])
	{
		if (exist_as_var(str, envp[index]))
		{
			return (index);
		}
		index++;
	}
	return (-1);
}

void	update_envp_with_extra_var(char **temp, t_shell *shell,
	int envp_length, char *new_envp_member)
{
	ft_memmove(temp, shell->envp, envp_length * sizeof(char *));
	temp[envp_length] = new_envp_member;
	free(shell->envp);
	shell->envp = temp;
}
