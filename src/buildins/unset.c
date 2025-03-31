/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:45:14 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/31 16:54:08 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_key(char *str)
{
	return (!ft_strchr(str, '='));
}

void	remove_var(int index, t_shell *shell, int envp_length)
{
	free(shell->envp[index]);
	ft_memmove(shell->envp + index, shell->envp + index + 1,
		sizeof(char *) * (envp_length - index - 1));
	shell->envp[envp_length - 1] = 0;
}

int	handle_unset(t_shell *shell)
{
	size_t	og_total_len;
	char	**args;
	int		index;

	args = shell->cmds->arg;
	if (!args)
		return (0);
	while (*args)
	{
		if (is_key(*args))
		{
			og_total_len = count_split(shell->envp);
			if (!og_total_len)
				return (0);
			index = get_envp_var_index(*args, shell);
			if (index != -1)
				remove_var(index, shell, og_total_len);
		}
		args++;
	}
	return (0);
}
