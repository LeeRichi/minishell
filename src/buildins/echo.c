/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:45:06 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/09 23:44:06 by mbutuzov         ###   ########.fr       */
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
//
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
			{
				handle_flag_helper(cmd_args, i);
				return ;
			}
			else
				*newline = 0;
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

int	handle_echo(char **cmd_args, t_shell *shell)
{
	int	i;
	int	newline;

	(void)shell;
	newline = 1;
	if (!cmd_args)
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
/*
static int  is_option(char *arg)
{
    if (*arg == '-' && *(arg + 1))
        arg++;
    while(*arg)
    {
        if (*arg != 'n')
            return (0);
        arg++;
    }
    return (1);
}

int    handle_echo(char **cmd, t_shell *shell)
{ 
    int    opt_n;
    (void)shell;
    opt_n = 0;
	if (!cmd)
	{
		ft_putstr_fd("\n", 1);
		return 0;
	}
    while (cmd)
    {
        if (is_option((*cmd)))
            opt_n = 1;
        else
            break;
	cmd++;
    }
    while (*cmd)
    {
        ft_putstr_fd(*cmd, 1);
        if (*(cmd + 1))
            ft_putstr_fd(" ", 1);
	cmd++;
    }
	    if (!opt_n)
        	ft_putstr_fd("\n", 1);
	return (1);
}
*/
