/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:20:21 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/31 22:30:44 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char *str)
{
	int			flag;
	long		result;
	long		long_buffer;

	flag = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			flag *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		long_buffer = result;
		result = 10 * result + (*str - 48);
		if (flag > 0 && result / 10 != long_buffer)
			return (-1);
		else if (flag < 0 && result / 10 != long_buffer)
			return (0);
		str++;
	}
	return (result * flag);
}
