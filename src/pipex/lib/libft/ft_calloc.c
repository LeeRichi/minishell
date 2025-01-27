/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:20:30 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/11/28 20:33:55 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	max;
	size_t	res;

	res = count * size;
	max = 0;
	max--;
	if (count && (max / count) < size)
		return (0);
	ptr = malloc(res);
	if (!ptr)
		return (0);
	ft_bzero(ptr, res);
	return (ptr);
}
