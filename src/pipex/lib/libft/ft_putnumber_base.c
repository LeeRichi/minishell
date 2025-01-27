/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnumber_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:09:16 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/08/01 20:20:04 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_number_length(long long number, int mo)
{
	int	count;

	count = 0;
	if (!number)
		return (1);
	while (number)
	{
		number /= mo;
		count++;
	}
	return (count);
}

static int	ft_abs(int i)
{
	if (i < 0)
		return (-i);
	return (i);
}

static int	write_num(long long number, char *radix, int length, int *count)
{
	int	mo;
	int	tmp;

	mo = ft_strlen(radix);
	if (length)
	{
		tmp = write_num(number / mo, radix, --length, count);
		if (tmp < 0)
			return (-1);
		return (ft_putchar_count(radix[ft_abs(number % mo)], count));
	}
	return (0);
}

int	ft_putnumber_base(long long number, char *radix)
{
	int	mo;
	int	number_length;
	int	output;
	int	count;

	count = 0;
	mo = ft_strlen(radix);
	number_length = get_number_length(number, mo);
	if (number < 0)
	{
		output = ft_putchar_count('-', &count);
		if (output == -1)
			return (-1);
	}
	output = write_num(number, radix, number_length, &count);
	if (output == -1)
		return (-1);
	if (number < 0)
		number_length++;
	return (number_length);
}
