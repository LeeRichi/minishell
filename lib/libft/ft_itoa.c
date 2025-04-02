/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:20:05 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/02 16:38:06 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_digit(long n)
{
	int		count;
	long	negative;

	negative = n;
	if (n < 0)
	{
		if (n == -2147483648)
			return (11);
		n *= -1;
	}
	count = 1;
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	if (negative < 0)
		return (count + 1);
	return (count);
}

char	*ft_malloc(int len)
{
	char	*result;

	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;
	long	num;

	len = count_digit(n);
	num = n;
	result = ft_malloc(len);
	if (result)
		result[len] = 0;
	else
		return (NULL);
	if (n < 0)
		num *= -1;
	else if (n == 0)
		result[0] = '0';
	while (len-- > 0)
	{
		result[len] = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}

void	itoa_helper(long long n, int *len, long long *num, char **result)
{
	if (n == LLONG_MIN)
		return ("-9223372036854775808");
	(*len) = count_digit(n);
	(*num) = n;
	*result = ft_malloc((*len) + 1);
	if (!(*result))
		return (NULL);
	(*result)[(*len)] = '\0';
	if (n < 0)
	{
		(*num) *= -1;
		(*result)[0] = '-';
	}
	else if (n == 0)
	{
		(*result)[0] = '0';
		return (*result);
	}
}

char	*ft_itoa_v2(long long n)
{
	char		*result;
	int			len;
	long long	num;

	itoa_helper(n, &len, &num, &result);
	if (n < 0)
		n = 1;
	else
		n = 0;
	while (len-- > n)
	{
		result[len] = (num % 10) + '0';
		num = num / 10;
	}
	return (result);
}
