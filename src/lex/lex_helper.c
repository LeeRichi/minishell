/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:28:12 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/01 18:41:50 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*str_append(t_shell *shell, char *str, char c)
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

char	*str_append_v2(t_shell *shell, char *str, char c, char *free_me)
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
		if (free_me)
			free(free_me);
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

char	*str_append_v4(t_shell *shell, char *str, char c, char **free_me)
{
	size_t	len;
	char	*new_str;

	if (str)
		len = ft_strlen(str);
	else
		len = 0;
	new_str = ft_calloc(len + 2, sizeof(char));
	if (!new_str)
	{
		if (str)
			free(str);
		while (free_me && *free_me)
			free(*(free_me++));
		malloc_fail_clean_exit(shell);
	}
	if (str)
	{
		ft_strcpy(new_str, str);
		free(str);
	}
	new_str[len] = c;
	return (new_str);
}

void	free_free_struc(t_free_struc *obj)
{
	if (obj)
	{
		if (obj->input)
			free(obj->input);
		if (obj->itoaed_str)
			free(obj->itoaed_str);
	}
}
