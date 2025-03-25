/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structlize_p2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:01:03 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/25 13:07:21 by chlee2           ###   ########.fr       */
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

//na = new_array
static void	malloc_new_array(t_shell *shell, char **na, char **array, int *i)
{
	na[*i] = ft_strdup(array[*i]);
	if (!na[*i])
		malloc_fail_clean_exit(shell);
	(*i)++;
}

char	**ft_add_to_array(t_shell *shell, char **array, const char *new_element)
{
	int		i;
	int		len;
	char	**new_array;

	len = 0;
	if (array)
	{
		while (array[len])
			len++;
	}
	new_array = malloc(sizeof(char *) * (len + 2));
	if (!new_array)
		malloc_fail_clean_exit(shell);
	i = 0;
	while (i < len)
		malloc_new_array(shell, new_array, array, &i);
	new_array[i] = ft_strdup(new_element);
	if (!new_array[i])
		malloc_fail_clean_exit(shell);
	new_array[i + 1] = NULL;
	if (array)
		free_matrix(array);
	return (new_array);
}
