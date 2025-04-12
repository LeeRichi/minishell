/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:27:48 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/12 22:26:59 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_var_ptr_from_envp(char *str, t_shell *shell)
{
	char	**envp;
	int		index;

	envp = shell->envp;
	index = 0;
	if (!envp)
		return (0);
	while (envp[index])
	{
		if (exist_as_var(str, envp[index]))
		{
			return (envp[index]);
		}
		index++;
	}
	return (0);
}

char	*ft_getenv_value_ptr(char *env_name, t_shell *shell)
{
	char	*var_ptr;

	var_ptr = get_var_ptr_from_envp(env_name, shell);
	if (!var_ptr)
		return (0);
	while (*var_ptr)
	{
		if (*var_ptr == '=')
		{
			var_ptr++;
			if (*var_ptr == 0)
				return (0);
			return (var_ptr);
		}
		var_ptr++;
	}
	return (0);
}
