/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:30:19 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/05/02 19:45:08 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			counter;
	unsigned char	*str_s1;
	unsigned char	*str_s2;

	counter = 0;
	str_s1 = (unsigned char *)s1;
	str_s2 = (unsigned char *)s2;
	while (counter < n)
	{
		if (str_s1[counter] != str_s2[counter])
			return (str_s1[counter] - str_s2[counter]);
		counter++;
	}
	return (0);
}
