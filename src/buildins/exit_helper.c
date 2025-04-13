/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:06:32 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/13 17:02:22 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_message_and_exit_v2(t_shell *shell, char **args, char *f_me)
{
	free(f_me);
	print_message_and_exit(shell, args);
}

static void	happy_exit_v2(t_shell *shell, char *f_me)
{
	if (!shell->pipex)
		printf("exit\n");
	free(f_me);
	free_with_code(shell, 0);
}

void	itoa_operation(t_shell *shell, long long new_way, char **args)
{
	char	*str_new_way;
	int		i;
	int		j;

	str_new_way = ft_itoa_v2(new_way);
	if (!str_new_way)
		malloc_fail_clean_exit(shell);
	i = 0;
	if (args[0][i] == '+')
		i++;
	while (args && args[0][i] == '0')
		i++;
	if (ft_strcmp(str_new_way, "0") == 0)
		happy_exit_v2(shell, str_new_way);
	j = 0;
	while (str_new_way[j] == '0')
		j++;
	if (ft_strcmp(str_new_way + j, "") == 0)
		print_message_and_exit_v2(shell, args, str_new_way);
	if (ft_strcmp(str_new_way + j, args[0] + i) != 0)
		print_message_and_exit_v2(shell, args, str_new_way);
	else if (ft_strcmp("-9223372036854775808", str_new_way + j) != 0)
		free(str_new_way);
}
