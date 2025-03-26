/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:38:15 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/25 15:21:13 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_message_and_exit(t_shell *shell, char **args)
{
	ft_putstr_fd("minishell: exit: ", STDERR);
	ft_putstr_fd(args[0], STDERR);
	ft_putendl_fd(": numeric argument required", STDERR);
	shell->exit_code = 2;
	ft_free_all(shell);
	exit(2);
}

static void	free_with_code(t_shell *shell, int code)
{
	ft_free_all(shell);
	shell->exit_code = code;
	exit(shell->exit_code);
}

int	handle_exit(t_shell *shell, char **args)
{
	int	atoied_value;
	int	local_exit_code;

	atoied_value = 0;
	if (args && args[0])
		atoied_value = ft_atoi(args[0]);
	if (args && args[0] && !atoied_value)
		print_message_and_exit(shell, args);
	else if (args && args[0] && args[1])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
		shell->exit_code = 1;
		return (1);
	}
	else if (args && args[0])
	{
		shell->exit_code = ft_atoi(args[0]) % 256;
		local_exit_code = shell->exit_code;
		free_with_code(shell, local_exit_code);
	}
	else
		free_with_code(shell, 0);
	return (SUCCESS);
}
