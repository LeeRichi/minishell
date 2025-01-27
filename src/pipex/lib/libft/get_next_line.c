/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:57:51 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/07/30 19:11:26 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_nl(char *s)
{
	char	*ptr;

	ptr = s;
	while (s && *s)
	{
		if (*s == '\n')
			return (s - ptr + 1);
		s++;
	}
	return (0);
}

static char	*ft_free(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = 0;
	}
	return (0);
}

static char	*fill_tb(char *total_buffer, char *buffer, int fd)
{
	int		read_bytes;
	char	*tmp;

	while (!check_nl(total_buffer))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			ft_free(&total_buffer);
			return (0);
		}
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = 0;
		tmp = total_buffer;
		if (total_buffer == 0)
			total_buffer = "";
		total_buffer = ft_strjoin(total_buffer, buffer);
		ft_free(&tmp);
	}
	return (total_buffer);
}

static char	*get_result(char **total_buffer)
{
	int		end;
	char	*tmp;
	char	*result;

	end = ft_strlen(*total_buffer);
	result = ft_substr(*total_buffer, 0, check_nl(*total_buffer));
	if (result == 0)
	{
		ft_free(total_buffer);
		return (0);
	}
	tmp = *total_buffer;
	*total_buffer = ft_substr(*total_buffer, check_nl(*total_buffer), end);
	ft_free(&tmp);
	if (total_buffer == 0)
	{
		ft_free(&result);
		return (0);
	}
	tmp = 0;
	return (result);
}

char	*get_next_line(int fd)
{
	static char		*total_buffer = 0;
	char			buffer[BUFFER_SIZE + 1];
	char			*result;

	result = 0;
	total_buffer = fill_tb(total_buffer, buffer, fd);
	if (check_nl(total_buffer))
		result = get_result(&total_buffer);
	else
	{
		if (total_buffer && *total_buffer)
		{
			result = ft_strdup(total_buffer);
			ft_free(&total_buffer);
			if (!result)
				return (0);
		}
		else if (total_buffer && !*total_buffer)
			result = ft_free(&total_buffer);
		else
			result = 0;
	}
	return (result);
}
