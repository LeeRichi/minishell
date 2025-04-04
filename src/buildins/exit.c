/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:38:15 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/04 23:23:02 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_message_and_exit(t_shell *shell, char **args)
{
	ft_putstr_fd("minishell: exit: ", STDERR);
	ft_putstr_fd(args[0], STDERR);
	ft_putendl_fd(": numeric argument required", STDERR);
	shell->exit_code = 2;
	ft_free_all(shell);
	exit(2);
}

void	free_with_code(t_shell *shell, int code)
{
	ft_free_all(shell);
	shell->exit_code = code;
	exit(shell->exit_code);
}

// void	itoa_operation(t_shell *shell, long long new_way, char **args)
// {
// 	char	*str_new_way;
// 	int		i;

// 	str_new_way = ft_itoa_v2(new_way);
// 	if (!str_new_way)
// 		malloc_fail_clean_exit(shell);
// 	i = 0;
// 	if (args[0][i] == '+')
// 		i++;
// 	while (args && args[0][i] == '0')
// 		i++;
// 	while (*str_new_way == '0')
// 		str_new_way++;
// 	if (ft_strcmp(str_new_way, "") == 0)
// 		print_message_and_exit(shell, args);
// 	if (ft_strcmp(str_new_way, args[0] + i) != 0)
// 	{
// 		free(str_new_way);
// 		print_message_and_exit(shell, args);
// 	}
// 	else if (ft_strcmp("-9223372036854775808", str_new_way) != 0)
// 		free(str_new_way);
// }

void	handle_exit_helper_helper(char **args, t_shell *shell,
			int *sign, int *i)
{
	if (!args || !args[0])
	{
		printf("exit \n");
		free_with_code(shell, 0);
		return ;
	}
	if (ft_strcmp(args[0], "") == 0)
	{
		//printf("0000\n");
		print_message_and_exit(shell, args);
	}
	if (args[0][*i] == '-')
	{
		*sign = -1;
		(*i)++;
	}
}

int ft_isnum(char k)
{
	return (k >= '0' && k <= '9');
}

void	handle_exit_helper(long long *new_way, char **args, t_shell *shell)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	handle_exit_helper_helper(args, shell, &sign, &i);
	if (!(ft_isnum(args[0][i]) || args[0][i] == '+'))
	{
		//perror("here1");
		print_message_and_exit(shell, args);
	}
	if (args[0][i] == '+')
		i++;
	if (!ft_isnum(args[0][i]))
	{
		//perror("here2");
		print_message_and_exit(shell, args);
	}
	while (args[0][i] >= '0' && args[0][i] <= '9')
	{
		if (sign > 0 && (*new_way > LLONG_MAX / 10
				|| (*new_way == LLONG_MAX / 10 && (args[0][i] - '0') > 7)))
				{
					// printf("1\n");
					print_message_and_exit(shell, args);
				}
		if (*new_way < LLONG_MIN / 10
			|| (*new_way == LLONG_MIN / 10 && (args[0][i] - '0') > 8))
			{
				// printf("2\n");
				print_message_and_exit(shell, args);
			}
		*new_way = *new_way * 10 + (args[0][i] - '0');
		i++;
	}
	if (args[0][i] != '\0')
	{
		// printf("3\n");
		print_message_and_exit(shell, args);
	}
	*new_way *= sign;
}

int	handle_exit(t_shell *shell, char **args)
{
	long long	new_way;

	new_way = LLONG_MIN;
	// printf("fuck: %lld !!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", new_way);

	// printf("hello : %lld !!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", -9223372036854775809);


	new_way = 0;
	// if (args && args[0] && args[1])
	// {
	// 	ft_putendl_fd("minishell: exit: too many arguments", STDERR);
	// 	shell->exit_code = 1;
	// 	return (1);
	// }
	handle_exit_helper(&new_way, args, shell);
	if (new_way < LLONG_MIN || new_way > LLONG_MAX)
	{
		// printf("4\n");
		print_message_and_exit(shell, args);
	}
	itoa_operation(shell, new_way, args);
	if (args && args[0] && args[1])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
		shell->exit_code = 1;
		return (1);
	}
	if (args && args[0] && !new_way)
	{
		// printf("5\n");
		print_message_and_exit(shell, args);
	}
	else if (args && args[0])
	{
		shell->exit_code = ft_atoi(args[0]) % 256;
		free_with_code(shell, shell->exit_code);
	}
	else
		free_with_code(shell, 0);
	return (SUCCESS);
}
