/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:38:15 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/02 00:36:37 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <limits.h>

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
	long long new_way;
	int sign;
	size_t i;
	
	i = 0;
	sign = 1;
	new_way = 0;
	atoied_value = 0;

	if (args[0][i] == '-')
	{
		sign = -1;
		i++;
	}
	while (args[0][i] >= '0' && args[0][i] <= '9') {
        if (sign > 0 && (new_way > LLONG_MAX / 10
			|| (new_way == LLONG_MAX / 10 && (args[0][i] - '0') > 7)))
				print_message_and_exit(shell, args);
			if (new_way < LLONG_MIN / 10
			|| (new_way == LLONG_MIN / 10 && (args[0][i] - '0') > 8))
				print_message_and_exit(shell, args);
        new_way = new_way * 10 + (args[0][i] - '0');
        i++;
    }
	if (args[0][i] != '\0')
		print_message_and_exit(shell, args);
	new_way *= sign;
	printf("new way lld: %lld\n", new_way);

	
	if (new_way < LLONG_MIN || new_way > LLONG_MAX)
	{
		printf("4\n");	
		print_message_and_exit(shell, args);
	}
	char *str_new_way = ft_itoa_v2(new_way);
	if (!str_new_way)
		malloc_fail_clean_exit(shell);
	if (ft_strcmp(str_new_way, args[0]) != 0)
	{
		free(str_new_way);
		print_message_and_exit(shell, args);
	}
	printf("str_new_way: %s\n", str_new_way);
	free(str_new_way);
	if (args && args[0])
		atoied_value = ft_atoi(args[0]);
	printf("atoied: %d\n", atoied_value);
	if (args && args[0] && !new_way)
	{
		printf("5\n");
		print_message_and_exit(shell, args);
	}
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
