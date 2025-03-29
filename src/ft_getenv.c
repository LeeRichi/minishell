/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:27:48 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/29 18:04:50 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *get_var_ptr_from_envp(char *str, t_shell *shell)
{
	char **envp = shell->envp;
	int	index;

	index = 0;
	while(envp[index])
	{
		if (exist_as_var(str, envp[index]))
		{
			return (envp[index]);
		}
		index++;
	}
	return (0);
}


char	*ft_getenv_value_ptr(char *env_name, t_shell *shell)
{
	char *var_ptr;
	int	equal_found;

	equal_found = 0;

	var_ptr = get_var_ptr_from_envp(env_name, shell);
	if (!var_ptr)
		return (0);
	while (*var_ptr)
	{
		if (*var_ptr == '=')
		{
			var_ptr++;
			if (*var_ptr == 0)
				return (0);
			return (var_ptr);
		}
		var_ptr++;
	}
	return (0);
}


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
			//TODO
			
				malloc_fail_clean_exit(shell);
			break ;
		}
		head = head->next;
	}
	free_key_value_list(pair);
	return (result);
}
