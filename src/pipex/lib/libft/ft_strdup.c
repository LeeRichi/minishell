/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:27:42 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/05/06 14:00:25 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	length;
	char	*ptr;

	length = ft_strlen(s1);
	ptr = malloc((length + 1) * sizeof(char));
	if (!ptr)
		return (0);
	while (*s1)
	{
		*ptr = *s1;
		ptr++;
		s1++;
	}
	*ptr = 0;
	return (ptr - length);
}
