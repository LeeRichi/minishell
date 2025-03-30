/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:45:14 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/30 20:00:45 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
char	*ft_strncpy(t_shell *shell, char *str, size_t n)
{
	size_t	len;
	char	*res;

	res = NULL;
	len = 0;
	while (str[len])
		len++;
	if (n > len)
		res = malloc((len + 1) * sizeof(char));
	else
		res = malloc((n + 1) * sizeof(char));
	if (!res)
		malloc_fail_clean_exit(shell);
	len = 0;
	while (str[len] && len < n)
	{
		res[len] = str[len];
		len++;
	}
	res[len] = '\0';
	return (res);
}

void	ft_cpy2envp(size_t found_index, size_t total, t_shell *shell)
{
	size_t	i;
	char	**new_envp;

	new_envp = malloc((total) * sizeof(char *));
	if (!new_envp)
		malloc_fail_clean_exit(shell);
	i = 0;
	while (i < found_index)
	{
		new_envp[i] = shell->envp[i];
		i++;
	}
	free(shell->envp[found_index]);
	while (found_index < total - 1)
	{
		new_envp[i] = shell->envp[found_index + 1];
		found_index++;
		i++;
	}
	new_envp[i] = 0;
	free(shell->envp);
	shell->envp = new_envp;
}

//og == og_total_len
//v_names == vn
void	loop_to_catch_you_and_free(t_shell *shell, size_t og, char ***vn)
{
	size_t	i;
	size_t	j;
	size_t	temp;

	temp = og;
	i = 0;
	while (i < og)
	{
		j = 0;
		while (shell->cmds->arg[j])
		{
			if (ft_strcmp((*vn)[i], shell->cmds->arg[j]) == 0)
			{
				ft_cpy2envp(i, og, shell);
				og--;
				i = 0;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < temp)
		free((*vn)[i++]);
	free((*vn));
}
*/
int is_key(char *str)
{
	return (!ft_strchr(str, '='));
}

int	handle_unset(t_shell *shell)
{
	size_t	og_total_len;
	char	**args;
	int	index;

	args = shell->cmds->arg;
	if (!shell->cmds->arg)
		return (0);
	while (*args)
	{
		if (is_key(*args))
		{
			og_total_len = count_split(shell->envp);
			if (!og_total_len)
				return (0);
			index = get_envp_var_index(*args, shell);
			if (index != -1)
			{
				free(shell->envp[index]);
				ft_memmove(shell->envp + index, shell->envp + index + 1, sizeof(char *) * (og_total_len  - index - 1));
				shell->envp[og_total_len - 1] = 0;
			}
		}
		args++;
	}
	return (0);
}
/*
int	handle_unset(t_shell *shell)
{
	char	**v_names;
	size_t	i;
	size_t	j;
	size_t	og_total_len;

	v_names = NULL;
	if (!shell->cmds->arg)
		return (0);
	og_total_len = count_split(shell->envp);
	v_names = malloc((og_total_len + 1) * sizeof(char *));
	if (!v_names)
		malloc_fail_clean_exit(shell);
	i = 0;
	while (shell->envp[i])
	{
		j = 0;
		while (shell->envp[i][j] != '=')
			j++;
		v_names[i] = ft_strncpy(shell, shell->envp[i], j);
		i++;
	}
	loop_to_catch_you_and_free(shell, og_total_len, &v_names);
	return (0);
}
*/
