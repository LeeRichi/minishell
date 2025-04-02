/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:06:32 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/02 16:31:48 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	itoa_operation(t_shell *shell, long long new_way, char **args)
{
	char	*str_new_way;
	int		i;

	str_new_way = ft_itoa_v2(new_way);
	if (!str_new_way)
		malloc_fail_clean_exit(shell);
	i = 0;
	if (args[0][i] == '+')
		i++;
	while (args && args[0][i] == '0')
		i++;
	while (*str_new_way == '0')
		str_new_way++;
	if (ft_strcmp(str_new_way, "") == 0)
		print_message_and_exit(shell, args);
	if (ft_strcmp(str_new_way, args[0] + i) != 0)
	{
		free(str_new_way);
		print_message_and_exit(shell, args);
	}
	else if (ft_strcmp("-9223372036854775808", str_new_way) != 0)
		free(str_new_way);
}
