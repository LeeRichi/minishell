/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structlize_p2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:01:03 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/24 20:56:51 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//count_specific == cs
int cs(char **tokens, char *nid)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], nid) == 0)
			count++;
		i++;
	}
	return count;
}

//temp function //clean up at the end
// count_redirections == cr
int cr(char **tokens)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], ">") == 0 ||
			ft_strcmp(tokens[i], ">>") == 0 || ft_strcmp(tokens[i], "<<") == 0)
			count++;
		i++;
	}
	return count;
}

//TODO: check ft_strdup
char	**ft_add_to_array(t_shell *shell, char **array, const char *new_element)
{
	int i;
	int len;
	char **new_array;

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
	{
		new_array[i] = ft_strdup(array[i]);
      	if (!new_array[i])
            malloc_fail_clean_exit(shell);
        i++;
	}
	new_array[i] = ft_strdup(new_element);
    if (!new_array[i])
		malloc_fail_clean_exit(shell);
    new_array[i + 1] = NULL;
    if (array)
        free_matrix(array);
    return new_array;
}

void	ft_nullize_struct(t_cmd *new_cmd)
{
	ft_bzero(new_cmd, sizeof(t_cmd));
}

void	ft_add_redirection(t_shell *shell, char ***array, char *file)
{
    *array = ft_add_to_array(shell, *array, file);
}