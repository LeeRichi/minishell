/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:27:48 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/25 13:10:36 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_getenv(char *env_name, t_shell *shell)
{
	t_key_value	*pair;
	t_key_value	*head;
	char		*result;

	result = NULL;
	head = NULL;
	pair = arr_to_key_value(shell);
	head = pair;
	while (head)
	{
		if (ft_strcmp(head->key, env_name) == 0)
		{
			result = ft_strdup(head->value);
			if (!result)
				malloc_fail_clean_exit(shell);
			break ;
		}
		head = head->next;
	}
	free_key_value_list(pair);
	return (result);
}
