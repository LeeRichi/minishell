/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:59:48 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/08/07 20:49:17 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_ctol_base(char digit, int base)
{
	long	num;

	if (!(ft_isdigit(digit) || ft_isupper(digit) || ft_islower(digit)))
		return (-1);
	num = (long)(digit - '0');
	if (base < 11)
	{
		if (num < (long)base)
			return (num);
		else
			return (-1);
	}
	if (ft_isupper(digit))
		num = (long)(digit - 'A' + 10);
	if (ft_islower(digit))
		num = (long)(digit - 'a' + 10);
	if (num < (long)base)
		return (num);
	return (-1);
}

static char	*resolve_endptr(int prefix, int digits, char *start, char *curr)
{
	if (prefix && !digits)
		return (start + 1);
	if (!digits)
		return (start);
	return (curr);
}

static void	set_endptr(char **endptr, char *start, int base)
{
	char	*temp;
	int		digits;
	int		prefix;

	if (!endptr)
		return ;
	temp = start;
	digits = 0;
	prefix = 0;
	while (ft_isspace(*temp))
		temp++;
	if (*temp == '-' || *temp == '+')
		temp++;
	if ((!base || base == 16) && *temp == '0'
		&& (*(temp + 1) == 'x' || *(temp + 1) == 'X'))
	{
		prefix++;
		temp += 2;
	}
	while (ft_ctol_base(*temp, base) != -1)
	{
		digits++;
		temp++;
	}
	*endptr = resolve_endptr(prefix, digits, start, temp);
}

//could be optimized
static long	ft_getnum(const char *str, long sign, int base)
{
	long	num;
	long	change;

	num = 0;
	while (ft_ctol_base(*str, base) != -1)
	{
		change = ft_ctol_base(*str, base) * sign;
		num += change;
		if ((sign > 0) && ((LONG_MAX - change) < (num - change)))
			return (LONG_MAX);
		if ((sign < 0) && ((LONG_MIN - change) > (num - change)))
			return (LONG_MIN);
		if (ft_ctol_base(*(str + 1), base) != -1)
		{
			if ((sign > 0) && (LONG_MAX / base) < num)
				return (LONG_MAX);
			if ((sign < 0) && (LONG_MIN / base) > num)
				return (LONG_MIN);
			num *= base;
		}
		str++;
	}
	return (num);
}

/*
	incorrect base unhandled
*/
long	ft_strtol(const char *nptr, char **endptr, int base)
{
	long	sign;
	char	*tmp;

	tmp = (char *)nptr;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
		sign = -sign;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	if (((!base || base == 16) && (*nptr == '0'))
		&& (*(nptr + 1) == 'x' || *(nptr + 1) == 'X'))
	{
		base = 16;
		nptr += 2;
	}
	else if (!base && *nptr == '0')
		base = 8;
	else if (!base)
		base = 10;
	set_endptr(endptr, tmp, base);
	return (ft_getnum(nptr, sign, base));
}
