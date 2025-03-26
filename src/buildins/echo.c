/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:45:06 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/25 15:54:08 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_flag_helper(char **cmd_args, int i)
{
	int	temp;

	temp = i;
	while (cmd_args[temp])
	{
		printf("%s", cmd_args[temp]);
		if (cmd_args[temp + 1])
			printf(" ");
		temp++;
	}
}

static void	handle_flag(char **cmd_args, int *newline)
{
	int	i;
	int	j;

	i = 0;
	while (cmd_args[i])
	{
		j = 1;
		while (cmd_args[i][j])
		{
			if (cmd_args[i][j] != 'n')
				handle_flag_helper(cmd_args, i);
			else
				(*newline) = 0;
			j++;
		}
		i++;
	}
}

static void	loop_print_each(char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i])
	{
		printf("%s", cmd_args[i]);
		if (cmd_args[i + 1])
			printf(" ");
		i++;
	}
}

int	handle_echo(char **cmd_args, t_shell *shell)
{
	int	i;
	int	newline;

	(void)shell;
	newline = 1;
	if (!cmd_args)
	{
		printf("\n");
		return (0);
	}
	i = 0;
	if (cmd_args[i] && cmd_args[i][0] == '-')
		handle_flag(cmd_args, &newline);
	else
		loop_print_each(cmd_args);
	if (newline)
		printf("\n");
	return (0);
}
