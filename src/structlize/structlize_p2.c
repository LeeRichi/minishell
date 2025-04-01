/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structlize_p2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:01:03 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/01 17:59:28 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//count_specific == cs
int	cs(char **tokens, char *nid)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], nid) == 0)
			count++;
		i++;
	}
	return (count);
}

// count_redirections == cr
// t = tokens
int	cr(char **t)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (t[i])
	{
		if (ft_strcmp(t[i], "<") == 0 || ft_strcmp(t[i], ">") == 0
			|| ft_strcmp(t[i], ">>") == 0 || ft_strcmp(t[i], "<<") == 0)
			count++;
		i++;
	}
	return (count);
}

char	**ft_add_to_array(t_shell *shell, char **array, const char *new_element)
{
	int		len;
	char	**new_array;

	len = 0;
	if (array)
	{
		while (array[len])
			len++;
	}
	new_array = ft_calloc(sizeof(char *), (len + 2));
	if (!new_array)
		malloc_fail_clean_exit(shell);
	ft_memcpy(new_array, array, len * (sizeof (char *)));
	new_array[len] = ft_strdup(new_element);
	if (!new_array[len])
	{
		free(new_array);
		malloc_fail_clean_exit(shell);
	}
	if (array)
		free(array);
	return (new_array);
}
