/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:45:14 by chlee2            #+#    #+#             */
/*   Updated: 2025/02/26 14:05:07 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *ft_strncpy(char *str, size_t n)
{
    size_t len;
	char *res = NULL;

	len = 0;
    while(str[len])
		len++;

	if (n > len)
		res = malloc((len + 1) * sizeof(char));
	else
		res = malloc((n + 1) * sizeof(char));
	if (!res)
	{
		perror("malloc failed on res");
		return (NULL);
	}
	len = 0;
	while(str[len] && len < n)
	{
		res[len] = str[len];
		len++;
	}
	res[len] = '\0';
	return (res);
}

void ft_cpy2envp(size_t found_index, size_t total, t_shell *shell)
{
	size_t i;
	char **new_envp;
	printf("total: %zu\n", total);
	printf("found_index: %zu\n", found_index);

	// new_envp = malloc((total - 1) * sizeof(char *));
	new_envp = malloc((total) * sizeof(char *));
	if (!new_envp)
	{
		perror("malloc failed on new_envp");
        return ;
	}
	i = 0;
	while (i < found_index)
	{
		new_envp[i] = shell->envp[i];
		i++;
	}
	printf("og: %zu\n", found_index);

//	while (found_index < total)
	while (found_index < total - 1)
	{
		printf("fi: %zu\n", found_index);
		new_envp[i] = shell->envp[found_index + 1];
		found_index++;
		i++;
	}
	new_envp[i] = NULL; // Null-terminate the new array

	// free(shell->envp); // Free old envp
	// printf("new_enp[%zu]: %s\n", i, new_envp[i]);
	shell->envp = new_envp;
}

void handle_unset(t_shell *shell)
{
    char **v_names = NULL;
    size_t i;
    size_t j;
    size_t og_total_len = 0;
	// char **updated_v_names = NULL;

	og_total_len = 0;
	while(shell->envp[og_total_len])
		og_total_len++;
	v_names = malloc((og_total_len + 1) * sizeof(char *));
	if (!v_names)
	{
		perror("malloc failed on v_names");
        return ;
	}
    i = 0;	//store all the var_names
    while (shell->envp[i])
    {
        j = 0;
        while (shell->envp[i][j] != '=') //skip until = to get j
            j++;
        v_names[i] = ft_strncpy(shell->envp[i], j);
        i++;
    }
	i = 0;
	// j = len;
	while (i < og_total_len)
    {
		j = 1;
		while (shell->tokens[j])
		{
			if (ft_strcmp(v_names[i], shell->tokens[j]) == 0)
			{
				// Remove the matching var_name from the environment
				ft_cpy2envp(i, og_total_len, shell);
				break;
			}
			j++;
		}
		i++;
    }
	// while(v_names[i])
	// {
    // 	if (ft_strcmp(v_names[i], input) == 0)
	// 	{
	// 		updated_v_names = malloc((len - 1) * sizeof(char *));
	// 		if (!updated_v_names)
	// 		{
	// 			perror("malloc failed on v_names");
	// 			return ;
	// 		}
	// 		len = i; //the matchcing index
	// 	}
	// 	i++;
	// }

	for (i = 0; i < og_total_len; i++)
        free(v_names[i]);
    free(v_names);


	// ft_cpy2envp(len, j, shell);
	/*
	i = 0;

	while (shell->envp[i])
	{
		printf("%zu: %s\n", i, shell->envp[i]);
		i++;
	}
	*/
}
