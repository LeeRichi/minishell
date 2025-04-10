/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:45:06 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/10 18:38:05 by chlee2           ###   ########.fr       */
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
			while (cmd_args[i][j] && cmd_args[i][j] == 'n')
				j++;
			if (cmd_args[i][j] && cmd_args[i][j] != 'n')
			{
				handle_flag_helper(cmd_args, i);
				return ;
			}
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
		ft_printf("%s", cmd_args[i]);
		if (cmd_args[i + 1])
			ft_printf(" ");
		i++;
	}
}

int is_one_of(char *s)
{
	if (ft_strchr(s, '>') || ft_strstr(s, ">>") || ft_strchr(s, '<'))
		return (1);
	return (0);
}

int	handle_echo(char **cmd_args, t_shell *shell)
{
	int	i;
	int	newline;

	// int y;
	// y = 1;
	
	newline = 1;
	if (!cmd_args || !shell->tokens)
	{
		ft_printf("\n");
		return (0);
	}

	// i = 0;
	// while (shell->tokens[i])
	// {
	// 	if (is_one_of(shell->tokens[i]))
	// 	{
	// 		i = 0;
	// 		if (shell->tokens[i] && shell->tokens[i][0] == '-')
	// 			handle_flag(shell->tokens, &newline);
	// 		else
	// 			loop_print_each(shell->tokens);
	// 		if (newline)
	// 			ft_printf("\n");
	// 		return (0);
	// 	}
	// 	i++;
	// }
	i = 0;
	if (cmd_args[i] && cmd_args[i][0] == '-')
		handle_flag(cmd_args, &newline);
	else
		loop_print_each(cmd_args);
	if (newline)
		ft_printf("\n");
	return (0);
}
