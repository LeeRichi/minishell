/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:04:07 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/08/01 20:19:16 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_count(char s, int *count)
{
	int	temp;

	temp = write(1, &s, 1);
	*count += temp;
	return (temp);
}

int	ft_putstr(char *s)
{
	int	count;
	int	err_track;

	count = 0;
	if (!s)
		s = "(null)";
	while (*s)
	{
		err_track = count;
		ft_putchar_count(*s, &count);
		if (err_track > count)
			return (-1);
		s++;
	}
	return (count);
}

static int	format_handler(const char *format, int count, va_list args)
{
	if (*format == 'c')
		return (ft_putchar_count((char)va_arg(args, int), &count));
	else if (*format == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (*format == 'p')
		return (ft_ptr_handler(va_arg(args, unsigned long)));
	else if (*format == 'd')
		return (ft_putnumber_base(va_arg(args, int), "0123456789"));
	else if (*format == 'i')
		return (ft_putnumber_base(va_arg(args, int), "0123456789"));
	else if (*format == 'u')
		return (ft_putnumber_base(va_arg(args, unsigned int), "0123456789"));
	else if (*format == 'x')
		return (ft_putnumber_base(va_arg(args, unsigned int),
				"0123456789abcdef"));
	else if (*format == 'X')
		return (ft_putnumber_base(va_arg(args, unsigned int),
				"0123456789ABCDEF"));
	else if (*format == '%')
		return (ft_putchar_count('%', &count));
	return (ft_putchar_count(*format, &count));
}

int	string_processor(const char *format, va_list args)
{
	int	result;
	int	count;

	result = 0;
	while (*format)
	{
		count = 0;
		if (*format == '%' && *(format + 1))
		{
			format++;
			count = format_handler(format, count, args);
		}
		else if (*format == '%')
			break ;
		else
			ft_putchar_count(*format, &count);
		if (count == -1)
			return (-1);
		result += count;
		format++;
	}
	return (result);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		result;

	va_start(args, format);
	result = string_processor(format, args);
	va_end(args);
	return (result);
}
