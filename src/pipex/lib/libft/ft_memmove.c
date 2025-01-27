/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:29:37 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/05/10 18:27:16 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*ch_src;
	char	*ch_dst;
	int		counter;

	ch_src = (char *)src;
	ch_dst = (char *)dst;
	if (!dst && !src)
		return (0);
	if (len && (!dst || !src))
		*ch_src = 'k';
	counter = 0;
	if (ch_dst < ch_src)
	{
		while (ch_src + len != ch_src + counter)
		{
			*(ch_dst + counter) = *(ch_src + counter);
			counter++;
		}
	}
	else
	{
		while (ch_src + len-- != ch_src)
			*(ch_dst + len) = *(ch_src + len);
	}
	return (dst);
}
