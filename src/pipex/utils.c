/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 23:23:18 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/04/11 15:12:17 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_split(char **args)
{
	char	**tmp;

	tmp = args;
	while (*args)
	{
		free(*args);
		args++;
	}
	free(tmp);
}

int	count_split(char **texts)
{
	int	i;

	//new
	if (!texts)
		return (0);

	i = 0;
	while (texts[i])
	{
		i++;
	}
	return (i);
}

void	ft_close(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

int	dup2_and_close(int *fd_from, int fd_to)
{
	int	dup_res;

	dup_res = 0;
	if (fd_from)
		dup_res = dup2(*fd_from, fd_to);
	ft_close(fd_from);
	if (dup_res == -1)
		return (-1);
	return (dup_res);
}
