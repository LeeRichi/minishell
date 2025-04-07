/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isNum_for_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:45:09 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/07 16:47:01 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isnum(char k)
{
	return (k >= '0' && k <= '9');
}

void	isnum_checker(t_shell *shell, char **args, int *i)
{
	if (!(ft_isnum(args[0][*i]) || args[0][*i] == '+'))
		print_message_and_exit(shell, args);
	if (args[0][*i] == '+')
		(*i)++;
	if (!ft_isnum(args[0][*i]))
		print_message_and_exit(shell, args);
}
