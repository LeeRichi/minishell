/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lvl_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:45:26 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/28 18:50:23 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//new_entry == ne
static void	replace_env_var(t_shell *shell, char **envp, char *key, char *ne)
{
	int		i;
	char	*formatted_key;

	formatted_key = ft_strjoin(key, "=");
	if (!formatted_key)
		malloc_fail_clean_exit(shell);
	i = 0;
	while (envp[i])
	{
		if (ft_strcmp(envp[i], formatted_key) == 0
			&& envp[i][0] == formatted_key[0])
		{
			free(envp[i]);
			envp[i] = ne;
			free(ne);
			free(formatted_key);
			return ;
		}
		i++;
	}
	free(ne);
	free(formatted_key);
}

//sh == shell
//nse == new_shlvl_entry
//ss == shlvl_str
static void	shell_level_ctrl_h(t_shell *sh, char *nse, char *ss)
{
	nse = ft_strjoin("SHLVL=", ss);
	if (!nse)
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
	char	*temp_str;

	new_shlvl_entry = NULL;
	shlvl_str = ft_getenv("SHLVL", shell);
	if (shlvl_str)
		shlvl = ft_atoi(shlvl_str) + 1;
	else
		shlvl = 1;
	temp_str = shlvl_str;
	shlvl_str = ft_itoa(shlvl);
	if (!shlvl_str)
	{
		free(shlvl_str);
		malloc_fail_clean_exit(shell);
	}
	else
		shell_level_ctrl_h(shell, new_shlvl_entry, shlvl_str);
	free(temp_str);
	replace_env_var(shell, shell->envp, "SHLVL", new_shlvl_entry);
	free(new_shlvl_entry);
}
