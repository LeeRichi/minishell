/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lvl_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:45:26 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/31 18:12:40 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//new_entry == ne
static int	replace_env_var(t_shell *shell, char **envp, char *key, char *ne)
{
	int	index;

	(void)envp;
	index = get_envp_var_index(key, shell);
	return (adjust_envp(ne, shell, index));
}

//sh == shell
//nse == new_shlvl_entry
//ss == shlvl_str
static void	shell_level_ctrl_h(t_shell *sh, char **nse, char *ss)
{
	*nse = ft_strjoin("SHLVL=", ss);
	if (!*nse)
	{
		free(ss);
		malloc_fail_clean_exit(sh);
	}
	free(ss);
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
	if (!replace_env_var(shell, shell->envp, "SHLVL", new_shlvl_entry))
	{
		free(new_shlvl_entry);
		malloc_fail_clean_exit(shell);
	}
}
