/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:45:06 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/12 22:24:58 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_flag_helper(char **cmd_args, int i)
{
	int	temp;

	temp = i;
	while (cmd_args[temp])
	{
		ft_printf("%s", cmd_args[temp]);
		if (cmd_args[temp + 1])
			ft_printf(" ");
		temp++;
	}
}

int	is_valid_n_flag(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (str[0] != '-')
		return (0);
	i = 1;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	handle_flag(char **cmd_args, int *newline)
{
	int	i;

	i = 0;
	while (cmd_args[i])
	{
		if (is_valid_n_flag(cmd_args[i]))
			(*newline) = 0;
		else
		{
			handle_flag_helper(cmd_args, i);
			break ;
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
		ft_printf("%s", cmd_args[i]);
		if (cmd_args[i + 1])
			ft_printf(" ");
		i++;
	}
}

// int	is_one_of(char *s)
// {
// 	if (ft_strchr(s, '>') || ft_strstr(s, ">>") || ft_strchr(s, '<'))
// 		return (1);
// 	return (0);
// }

int	handle_echo(char **cmd_args, t_shell *shell)
{
	int	i;
	int	newline;

	newline = 1;
	if (!cmd_args || !shell->tokens)
	{
		ft_printf("\n");
		return (0);
	}
	i = 0;
	if (cmd_args[i] && cmd_args[i][0] == '-')
		handle_flag(cmd_args, &newline);
	else
		loop_print_each(cmd_args);
	if (newline)
		ft_printf("\n");
	return (0);
}
