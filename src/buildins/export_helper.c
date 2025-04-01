/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:24:18 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/01 16:17:48 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		update_envp_with_extra_var(temp, shell,
			envp_length, new_envp_member);
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
	char		*equal_pos;
	int			var_index;

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
