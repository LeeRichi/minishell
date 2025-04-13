/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:14:41 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/13 17:17:42 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ac_checker(int ac)
{
	if (ac != 1)
	{
		ft_putstr_fd("Usage ./minishell\n", 2);
		exit(EXIT_FAILURE);
	}
}
