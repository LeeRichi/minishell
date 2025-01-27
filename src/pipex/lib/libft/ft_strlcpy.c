/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:20:08 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/05/02 20:13:22 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	counter;

	src_len = 0;
	counter = 0;
	while (src[src_len])
	{
		src_len++;
	}
	if (!dstsize)
		return (src_len);
	while (counter < dstsize - 1 && src[counter])
	{
		dst[counter] = src[counter];
		counter++;
	}
	if (dstsize)
		dst[counter] = 0;
	return (src_len);
}
