/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:20:14 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/04/26 18:08:18 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_write_num(int n, int fd, int length)
{
	char	digit;

	if (--length)
		ft_write_num(n / 10, fd, length);
	if (n < 0)
		digit = (-1) * (n % 10) + '0';
	else
		digit = (n % 10) + '0';
	write(fd, &digit, 1);
}

static int	ft_get_num_length(int n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	length;

	length = ft_get_num_length(n);
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n < 0)
		write(fd, "-", 1);
	ft_write_num(n, fd, length);
}
