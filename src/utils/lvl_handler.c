/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lvl_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:45:26 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/10 15:32:00 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void replace_env_var(char **envp, char *key, char *new_entry)
{
	int i;
	char *formatted_key;

	formatted_key = ft_strjoin(key, "=");
	i = 0;
	while(envp[i])
	{
		if (ft_strcmp(envp[i], formatted_key) == 0 && envp[i][0] == formatted_key[0])
		{
			free(envp[i]);
			envp[i] = new_entry;
			free(formatted_key);
			return;
		}
		i++;
	}
	free(formatted_key); 
}

void shell_level_ctrl(t_shell *shell)
{
	char *shlvl_str;
	int shlvl;
	char *new_shlvl_entry;

	new_shlvl_entry = NULL;
	shlvl_str = ft_getenv("SHLVL", shell);
	if (shlvl_str)
		shlvl = ft_atoi(shlvl_str) + 1;
	else
		shlvl = 1;
	shlvl_str = ft_itoa(shlvl);
	if (shlvl_str)
	{
		setenv("SHLVL", shlvl_str, 1);
		new_shlvl_entry = ft_strjoin("SHLVL=", shlvl_str);
		free(shlvl_str);
	}
	replace_env_var(shell->envp, "SHLVL", new_shlvl_entry);
	free(new_shlvl_entry);
}
