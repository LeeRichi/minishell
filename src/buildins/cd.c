/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:38:17 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/29 18:09:22 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
static int	env_oldpwd_handler(t_shell *shell, char **custom, char *old)
{
	char	*temp;

	custom[1] = ft_strjoin("OLDPWD=", "");
	if (!custom[1])
	{
		free(old);
		malloc_fail_clean_exit(shell);
	}
	temp = ft_strjoin(custom[1], old);
	if (!temp)
	{
		free(old);
		malloc_fail_clean_exit(shell);
	}
	free(custom[1]);
	free(old);
	custom[1] = temp;
	return (0);
}

static int	env_pwd_handler(t_shell *shell, char *old)
{
	char	**custom;
	char	*cwd;
	char	path[PATH_MAX];

	cwd = NULL;
	custom = ft_calloc(sizeof(char *), 3);
	if (!custom)
	{
		free(old);
		malloc_fail_clean_exit(shell);
	}
	env_oldpwd_handler(shell, custom, old);
	custom[0] = ft_strjoin("PWD=", "");
	if (!custom[0])
		malloc_fail_clean_exit(shell);
	if (set_pwd(custom, shell, cwd, path) != 0)
	{
		free_matrix(custom);
		return (-1);
	}
	handle_export(shell, custom);
	free_matrix(custom);
	return (0);
}
*/
int update_envp_pwd_old_pwd(char *old, t_shell *shell)
{
	int var_index;
	char *var_key_val;
	char path[PATH_MAX];
	
	var_index = get_envp_var_index("PWD", shell);
	// THINK
	var_key_val = ft_strjoin("PWD=",  getcwd(path, PATH_MAX));
	if (!var_key_val)
		return (0);
	if (!adjust_envp(var_key_val, shell, var_index))
	{
		free(var_key_val);
		return (0);
	}
	free(var_key_val);
	var_index = get_envp_var_index("OLDPWD", shell);
	var_key_val = ft_strjoin("OLDPWD=",  old);
	if (!var_key_val)
		return (0);
	if (!adjust_envp(var_key_val, shell, var_index))
	{
		free(var_key_val);
		return (0);
	}
	free(var_key_val);
	return (1);
	
//		return (1);
}
/*
static int	cd_to(t_shell *shell, char **args, char *old)
{
	if (args [1])
	{
		free(old);
		ft_printf_fd(STDERR, " too many arguments\n");
		shell->exit_code = 1;
		return (1);
	}
	if (chdir(args[0]) != 0)
	{
		
		if (ft_strcmp(args[0], "-") != 0)
		{
			free(old);
			ft_printf_fd(STDERR, SHELL_NAME": cd: No such file or directory\n");
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
*/
static int	cd_to(t_shell *shell, char **args)
{
	if (chdir(args[0]) != 0)
	{
		// TODO: check if needed
		if (ft_strcmp(args[0], "-") != 0)
		{
			ft_printf_fd(STDERR, SHELL_NAME": cd: No such file or directory\n");
			shell->exit_code = 1;
			return (1);
		}
	}
	return (0);
}
/*
static int	flag_case(t_shell *shell, char *old, int i)
{
	char	*home;

	home = ft_getenv_value_ptr("HOME", shell);
	if (home)
	{
		if (i)
			printf("%s\n", home);
		chdir(home);
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
*/

static int	cd_home(t_shell *shell, int i, int *cd_fail)
{
	char	*home;

	home = ft_getenv_value_ptr("HOME", shell);
	if (home)
	{
		if (i)
			printf("%s\n", home);
		chdir(home);
//		if (!update_env_cd(shell, old))
//			return (1);
		return (0);
	}
	else
	{
		*cd_fail = 1;
		printf("HOME not set.\n");
		shell->exit_code = 1;
		return (1);
	}
}

/*
	get pwd to make it old pwd
	
	get home path for -, -- and no args
	if no home var -- error message



*/

/*
	cd asdasdasdasd
	wrong message
*/
/*
	cd to home
	cd to location
	update the env vars
	
*/

int	handle_cd(char **args, t_shell *shell)
{
	char	*old;
	char	pwd_path[PATH_MAX];
	int	cd_fail;

	cd_fail = 0;
	
	if (args [1])
	{
		ft_printf_fd(STDERR, " too many arguments\n");
		shell->exit_code = 1;
		return (1);
	}
	old = 0;
	if (getcwd(pwd_path, PATH_MAX))
		old = pwd_path;
	else
		old = ft_getenv_value_ptr("PWD", shell);/*
	if (!old)
	{
		ft_printf_fd(STDERR, "PWD not found\n");
		shell->exit_code = 1;
		return (1);
	}
	*/
	if (!args || ft_strcmp(args[0], "--") == 0)
		cd_home(shell, 0, &cd_fail);
	else if (ft_strcmp(args[0], "-") == 0)
		cd_home(shell, 1, &cd_fail);
	else if (args[0])
	{
		if (cd_to(shell, args))
			return (1);
	}
	if (!cd_fail)
	{
		if (!update_envp_pwd_old_pwd(old, shell))
			return (1);
	}
		
	

	/*
	if (!args || ft_strcmp(args[0], "--") == 0)
		flag_case(shell, old, 0);
	else if (ft_strcmp(args[0], "-") == 0)
		flag_case(shell, old, 1);
	else if (ft_strcmp(args[0], ".") == 0)
	{
		free(old);
		return (0);
	}
	*/
	
	return (0);
}

/*
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
	{
		free(old);
		return (0);
	}
	else if (args[0])
	{
		if (cd_to(shell, args, old))
			return (1);
	}
	return (0);
}

*/