/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:38:15 by chlee2            #+#    #+#             */
/*   Updated: 2025/02/14 15:06:32 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_isNum(char *s)
{
    int i;
    i = 0;

    if (s == NULL)
        return (0);
    if (s[0] == '-')
        i++;
    while (s[i])
    {
        if (s[i] < '0' || s[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

void handle_exit(t_shell *shell, char **args)
{
    ft_putstr_fd("exit\n", STDOUT);
    if (args[1] && args[2])
    {
		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
        shell->exit_code = STDERR;
        exit(shell->exit_code);
    }
    else if (args[1] && !ft_isNum(args[1]))
    {
        ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(args[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
        shell->exit_code = NONE_NUMERIC_EXIT_CODE;
        exit(NONE_NUMERIC_EXIT_CODE);
    }
    else if (args[1]) //valid //with exit and 1 numeric arg
    {
        shell->exit_code = ft_atoi(args[1]) % 256;
        exit(ft_atoi(args[1]) % 256);
    }
    else //default //valid //only exit
    {
        exit(shell->exit_code);
        // shell->exit_code = 0;
        // exit(0);
    }
	// printf("%d\n", shell->exit_code);
}
