/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:33:14 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/05/03 16:29:00 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_int_length(int n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}

static void	ft_fill_string(char *result, int n, int length)
{
	int	current;

	if (n < 0)
	{
		length++;
		result[0] = '-';
	}
	current = 0;
	if (n == 0)
	{
		result[0] = '0';
	}
	while (n)
	{
		if (n < 0)
			current = (-1) * (n % 10);
		else
			current = n % 10;
		n = n / 10;
		length--;
		result[length] = current + '0';
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	int		length;

	length = ft_get_int_length(n);
	if (n < 0)
		result = malloc(sizeof(char) * (length + 2));
	else
		result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (0);
	ft_fill_string(result, n, length);
	if (n < 0)
		result[length + 1] = 0;
	else
		result[length] = 0;
	return (result);
}
