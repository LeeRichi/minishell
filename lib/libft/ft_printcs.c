/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:15:38 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/28 19:08:54 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printchar(char c)
{
	if (write(1, &c, 1) != 1)
		return (-1);
	return (1);
}

int	printstr(int fd, char *s)
{
	int	count;

	count = 0;
	if (!s)
		return (printstr(fd, "(null)"));
	count = write(fd, s, ft_strlen(s));
	if (count == -1)
	{
		perror("write failed");
		return (-1);
	}
	return (count);
}
