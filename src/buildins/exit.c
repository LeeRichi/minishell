/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:38:15 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/13 17:58:02 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int ft_isNum(char *s)
// {
//     int i;
//     i = 0;

//     if (s == NULL)
//         return (0);
//     if (s[0] == '-')
//         i++;
//     while (s[i])
//     {
//         if (s[i] < '0' || s[i] > '9')
//             return (0);
//         i++;
//     }
//     return (1);
// }

void temp_cleanup(t_shell *shell)
{
    t_pipex *pipex = shell->pipex;

	if (pipex)
	{
		free_pipex(*pipex);
		shell->pipex = 0;
	}
	clear_cmds(shell);
    //ft_free_all(shell);
}

int handle_exit(t_shell *shell, char **args)
{
    int atoied_value;

	atoied_value = 0;
    if (args && args[0])
		atoied_value = ft_atoi(args[0]);
	
    //fuck temp
    // ft_putstr_fd("exit\n", STDOUT);
    if (args && args[0] && args[1])
    {
		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
        shell->exit_code = ERROR;
        /*TODO: cleanup*/
        //temp_cleanup(shell);
        ft_free_all(shell);
        exit(ERROR);
    }
    else if (args && args[0] && !atoied_value)
    {
        ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(args[0], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
        shell->exit_code = STDERR;
        /*TODO: cleanup*/
        //temp_cleanup(shell);
        ft_free_all(shell);
        exit(STDERR);
    }
    else if (args && args[0]) //valid //with exit and 1 numeric arg
    {
        shell->exit_code = ft_atoi(args[0]) % 256;
        int some = shell->exit_code;
        /*TODO: cleanup*/
        //temp_cleanup(shell);
        ft_free_all(shell);

        // return (ft_atoi(args[0]) % 256);
       
        exit(some);
    }
    else //default //valid //only exit
    {
        /*TODO: cleanup*/
        //temp_cleanup(shell);
        ft_free_all(shell);
        // printf("code is %d\n", shell->exit_code);
        // exit(0);
        shell->exit_code = 0;
        exit(shell->exit_code);
    }
	// printf("%d\n", shell->exit_code);
    return (SUCCESS);
}
