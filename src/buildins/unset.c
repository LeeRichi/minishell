/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:45:14 by chlee2            #+#    #+#             */
/*   Updated: 2025/02/18 21:46:23 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *ft_strncpy(char *str, size_t n) //"PATH=FUCK", 4
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

void handle_unset(t_shell *shell, char *input)
{
    char **v_names = NULL;
    size_t i;
    size_t j;
    size_t len = 0;
	// char **updated_v_names = NULL;

	len = 0;
	while(shell->envp[len])
		len++;
	v_names = malloc((len + 1) * sizeof(char *));
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
	while (i < len)
    {
        if (ft_strcmp(v_names[i], input) == 0)
        {
            // Remove the matching var_name from the environment
            ft_cpy2envp(i, len, shell);
            break;
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
	
	for (i = 0; i < len; i++)
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
