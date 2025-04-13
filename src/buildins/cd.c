/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:38:17 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/13 16:34:15 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_complicated_pwd(char *old, char *cd_arg)
{
	char	*tabs[5];

	tabs[0] = "PWD=";
	tabs[1] = old;
	tabs[2] = "/";
	tabs[3] = cd_arg;
	tabs[4] = 0;
	return (ft_split_join(tabs, 0));
}

static int	update_var_key_val_envp_and_free(t_shell *shell,
	char *var_key_val)
{
	int	var_index;

	if (!var_key_val)
		return (0);
	var_index = get_envp_var_index("PWD", shell);
	if (!adjust_envp(var_key_val, shell, var_index))
	{
		free(var_key_val);
		return (0);
	}
	free(var_key_val);
	return (1);
}

int	replace_pwd(char *old, t_shell *shell, char **cd_args)
{
	int		no_var_key_val;
	char	*var_key_val;
	char	path[PATH_MAX];

	no_var_key_val = 0;
	var_key_val = 0;
	if (getcwd(path, PATH_MAX))
		var_key_val = ft_strjoin("PWD=", path);
	else if (old && cd_args)
	{
		ft_printf_fd(STDERR, "getcwd fail\n");
		if (*cd_args)
			var_key_val = get_complicated_pwd(old, *cd_args);
		else
			no_var_key_val = 1;
	}
	else
		no_var_key_val = 1;
	if (!var_key_val && no_var_key_val)
		return (1);
	if (update_var_key_val_envp_and_free(shell, var_key_val))
		return (1);
	return (0);
}

int	replace_old_pwd(char *old, t_shell *shell)
{
	int		var_index;
	char	*var_key_val;

	var_index = get_envp_var_index("OLDPWD", shell);
	var_key_val = ft_strjoin("OLDPWD=", old);
	if (!var_key_val)
		return (0);
	if (!adjust_envp(var_key_val, shell, var_index))
	{
		free(var_key_val);
		return (0);
	}
	free(var_key_val);
	return (1);
}

int	update_envp_pwd_old_pwd(char *old, t_shell *shell, char **cd_args)
{
	if (replace_old_pwd(old, shell) && replace_pwd(old, shell, cd_args))
		return (1);
	malloc_fail_clean_exit(shell);
	return (0);
}
