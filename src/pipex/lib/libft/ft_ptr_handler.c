/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:24:43 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/08/01 20:19:40 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_number_length(unsigned long number, int mo)
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

static int	write_num(unsigned long number, char *radix, int length, int *count)
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

static int	ft_putnumber_base_ptr(unsigned long number, char *radix)
{
	int	mo;
	int	number_length;
	int	output;
	int	count;

	count = 0;
	mo = ft_strlen(radix);
	number_length = get_number_length(number, mo);
	output = write_num(number, radix, number_length, &count);
	if (output == -1)
		return (-1);
	return (number_length);
}

int	ft_ptr_handler(unsigned long num)
{
	int	count;
	int	total;

	count = 0;
	total = 0;
	count = ft_putstr("0x");
	if (count < 0)
		return (-1);
	total += count;
	count = ft_putnumber_base_ptr(num, "0123456789abcdef");
	if (count < 0)
		return (-1);
	total += count;
	return (total);
}
