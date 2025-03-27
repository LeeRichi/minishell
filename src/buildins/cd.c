/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:38:17 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/27 14:25:54 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	env_oldpwd_handler(t_shell *shell, char **custom, char *old)
{
	char	*temp;

	custom[1] = ft_strjoin("OLDPWD=", "");
	if (!custom[1])
		malloc_fail_clean_exit(shell);
	temp = ft_strjoin(custom[1], old);
	if (!temp)
		malloc_fail_clean_exit(shell);
	free(custom[1]);
	custom[1] = temp;
	return (0);
}

// int	cwd_fail(t_shell *shell, char **custom)
// {
// 	ft_printf_fd(STDERR, "getcwd failed\n");
// 	shell->exit_code = 1;
// 	free_matrix(custom);
// 	return (1);
// }

static int	env_pwd_handler(t_shell *shell, char *old)
{
	char	**custom;
	char	*cwd;
	char	*temp;
	char	path[PATH_MAX];

	custom = malloc(sizeof(char *) * 3);
	if (!custom)
		malloc_fail_clean_exit(shell);
	env_oldpwd_handler(shell, custom, old);
	custom[0] = ft_strjoin("PWD=", "");
	if (!custom[0])
		malloc_fail_clean_exit(shell);
	cwd = getcwd(path, PATH_MAX);
	if (!cwd)
		return (cwd_fail(shell, custom));
	temp = ft_strjoin(custom[0], cwd);
	if (!temp)
		malloc_fail_clean_exit(shell);
	free(custom[0]);
	custom[0] = temp;
	custom[2] = NULL;
	handle_export(shell, custom);
	free_matrix(custom);
	return (0);
}

static int	cd_to(t_shell *shell, char **args, char *old)
{
	if (args [1])
	{
		ft_printf_fd(STDERR, " too many arguments\n");
		shell->exit_code = 1;
		return (1);
	}
	if (chdir(args[0]) != 0)
	{
		if (ft_strcmp(args[0], "-") != 0)
		{
			ft_printf_fd(STDERR, " cd\n");
			shell->exit_code = 1;
			return (1);
		}
	}
	else
	{
		if (env_pwd_handler(shell, old))
			return (1);
	}
	return (0);
}

static int	flag_case(t_shell *shell, char *old, int i)
{
	char	*home;

	home = ft_getenv("HOME", shell);
	if (home)
	{
		if (i)
			printf("%s\n", home);
		chdir(home);
		free(home);
		if (env_pwd_handler(shell, old))
			return (1);
		return (0);
	}
	else
	{
		printf("HOME not set.\n");
		shell->exit_code = 1;
		return (1);
	}
}

int	handle_cd(char **args, t_shell *shell)
{
	char	*old;

	old = ft_getenv("PWD", shell);
	if (!old)
	{
		ft_printf_fd(STDERR, "ft_getenv failed\n");
		shell->exit_code = 1;
		return (1);
	}
	if (!args || ft_strcmp(args[0], "--") == 0)
		flag_case(shell, old, 0);
	else if (ft_strcmp(args[0], "-") == 0)
		flag_case(shell, old, 1);
	else if (ft_strcmp(args[0], ".") == 0)
		return (0);
	else if (args[0])
	{
		if (cd_to(shell, args, old))
			return (1);
	}
	return (0);
}
