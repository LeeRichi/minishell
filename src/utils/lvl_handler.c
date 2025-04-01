/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lvl_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:45:26 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/01 16:44:03 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	replace_env_var(t_shell *shell, char *key, char *new_entry)
{
	int	index;

	index = get_envp_var_index(key, shell);
	return (adjust_envp(new_entry, shell, index));
}

static void	shell_level_ctrl_h(t_shell *shell,
	char **new_entry, char *shlvl_str)
{
	*new_entry = ft_strjoin("SHLVL=", shlvl_str);
	free(shlvl_str);
	if (!*new_entry)
		malloc_fail_clean_exit(shell);
}

void	shell_level_ctrl(t_shell *shell)
{
	char	*shlvl_str;
	int		shlvl;
	char	*new_shlvl_entry;
	char	*itoaed_str;

	new_shlvl_entry = NULL;
	shlvl_str = ft_getenv_value_ptr("SHLVL", shell);
	if (shlvl_str)
		shlvl = ft_atoi(shlvl_str) + 1;
	else
		shlvl = 1;
	itoaed_str = ft_itoa(shlvl);
	if (!itoaed_str)
		malloc_fail_clean_exit(shell);
	else
		shell_level_ctrl_h(shell, &new_shlvl_entry, itoaed_str);
	if (!replace_env_var(shell, "SHLVL", new_shlvl_entry))
	{
		free(new_shlvl_entry);
		malloc_fail_clean_exit(shell);
	}
	free(new_shlvl_entry);
}
