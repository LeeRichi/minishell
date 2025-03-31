/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_helper_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:02:51 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/31 18:03:03 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*str_append_v3(t_shell *shell, char *str, char c, t_free_struc *free_v3)
{
	size_t	len;
	char	*new_str;

	if (str)
		len = ft_strlen(str);
	else
		len = 0;
	new_str = malloc(len + 2);
	if (!new_str)
	{
		if (str)
			free(str);
		if (free_v3)
			free_free_struc(free_v3);
		malloc_fail_clean_exit(shell);
	}
	if (str)
	{
		ft_strcpy(new_str, str);
		free(str);
	}
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}

char	*get_env_value(char *env_name, t_shell *shell)
{
	char	*env_value_ptr;

	env_value_ptr = ft_getenv_value_ptr(env_name, shell);
	if (!env_value_ptr)
		return (NULL);
	return (env_value_ptr);
}

int	ft_start_with(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		if (str[i] != c)
			return (0);
		else
			return (1);
		i++;
	}
	return (0);
}

char	*ft_start_with_specials(char *str)
{
	const char	**special_chars;
	int			i;
	int			j;
	size_t		len;

	special_chars = (const char *[]){">>", "<<", ">", "<", "|", NULL};
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	j = 0;
	while (special_chars[j] != NULL)
	{
		len = strlen(special_chars[j]);
		if (ft_strncmp(&str[i], special_chars[j], len) == 0)
			return ((char *)special_chars[j]);
		j++;
	}
	return (NULL);
}

int	ft_end_with(char *str, char c)
{
	int	len;

	len = ft_strlen(str);
	while (len > 0)
	{
		len--;
		while (str[len] == ' ' || str[len] == '\t' || str[len] == '\n')
			len--;
		if (str[len] == c)
			return (1);
		else
			return (0);
		len--;
	}
	return (0);
}
