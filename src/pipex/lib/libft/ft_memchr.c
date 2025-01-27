/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:10:35 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/05/02 17:13:55 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*alt;
	unsigned char	character;

	alt = (unsigned char *)s;
	character = c;
	while (n--)
	{
		if (*alt == character)
			return (alt);
		alt++;
	}
	return (0);
}
