/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:08:13 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/11 17:27:59 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}

// #include <malloc.h>

// void *ft_realloc(void *ptr, size_t size)
// {
//     void *new_ptr;
//     size_t old_size;

//     if (!ptr)
//         return (malloc(size));  // If ptr is NULL, allocate new memory of the given size.

//     if (size == 0)
//     {
//         free(ptr);
//         return (NULL);  // If size is 0, free the memory and return NULL.
//     }

//     old_size = malloc_usable_size(ptr);  // Get the actual size of the old memory block.
//     new_ptr = malloc(size);  // Allocate new memory of the requested size.

//     if (!new_ptr)
//         return (NULL);  // If malloc fails, return NULL.

//     // Copy the smaller of the old size and new size to avoid overflows.
//     ft_memcpy(new_ptr, ptr, (old_size < size) ? old_size : size);

//     free(ptr);  // Free the old memory.

//     return (new_ptr);  // Return the pointer to the new memory block.
// }

