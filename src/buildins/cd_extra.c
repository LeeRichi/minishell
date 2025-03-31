/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:57:25 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/31 20:57:57 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cd_to(char *dest)
{
	if (chdir(dest))
	{
		perror(SHELL_NAME": cd");
		return (1);
	}
	return (0);
}

static int	cd_to_var(t_shell *shell, char *var_key)
{
	char	*var_value;

	var_value = ft_getenv_value_ptr(var_key, shell);
	if (var_value)
	{
		if (cd_to(var_value))
			return (0);
		return (1);
	}
	else
	{
		ft_printf_fd(2, "%s not set.\n", var_key);
		return (0);
	}
}

static char	*get_pwd_before_cd(t_shell *shell, int *no_pwd, char *pwd_path)
{
	char	*old;

	old = 0;
	if (getcwd(pwd_path, PATH_MAX))
		old = pwd_path;
	else if (ft_getenv_value_ptr("PWD", shell))
	{
		old = ft_getenv_value_ptr("PWD", shell);
	}
	else
		*no_pwd = 1;
	return (old);
}

static int	try_chdir(char **args, t_shell *shell)
{
	int		cd_fail;
	char	new_pwd_path[PATH_MAX];

	cd_fail = 0;
	if (!args || ft_strcmp(args[0], "--") == 0)
		cd_fail = cd_to_var(shell, "HOME");
	else if (ft_strcmp(args[0], "-") == 0)
	{
		cd_fail = cd_to_var(shell, "OLDPWD");
		if (!cd_fail)
		{
			if (getcwd(new_pwd_path, PATH_MAX))
				ft_printf_fd(2, "%s\n", new_pwd_path);
		}
	}
	else if (args[0])
		cd_fail = cd_to(args[0]);
	return (cd_fail);
}

int	handle_cd(char **args, t_shell *shell)
{
	char	*old;
	char	pwd_path[PATH_MAX];
	int		cd_fail;
	int		no_pwd;

	cd_fail = 0;
	no_pwd = 0;
	if (args && args [1])
	{
		ft_printf_fd(STDERR, " too many arguments\n");
		shell->exit_code = 1;
		return (1);
	}
	old = get_pwd_before_cd(shell, &no_pwd, pwd_path);
	cd_fail = try_chdir(args, shell);
	if (cd_fail || (!cd_fail && !no_pwd
			&& !update_envp_pwd_old_pwd(old, shell, args)))
		return (1);
	return (0);
}
