/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:17:57 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/07/05 17:42:28 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*put_ul(size_t *len, void *ptr, unsigned long long num)
{
	unsigned long long	*chunk;

	chunk = (unsigned long long *)ptr;
	while (*len >= sizeof(unsigned long long))
	{
		*chunk = num;
		chunk++;
		*len -= sizeof(unsigned long long);
	}
	return ((void *)chunk);
}

void	*ft_memset(void *mem, int c, size_t len)
{
	unsigned long long	tmp;
	unsigned char		*str;
	void				*ptr;
	int					chunk_size;

	tmp = 0;
	chunk_size = (int) sizeof(unsigned long long);
	ptr = mem;
	while (chunk_size > 0)
	{
		tmp += (unsigned long long)(unsigned char)c;
		if (chunk_size > 1)
			tmp = tmp << 8;
		chunk_size--;
	}
	if (len >= sizeof(unsigned long long))
		ptr = put_ul(&len, mem, tmp);
	str = (unsigned char *)ptr;
	while (len--)
	{
		*str = (unsigned char)c;
		str++;
	}
	return (mem);
}
