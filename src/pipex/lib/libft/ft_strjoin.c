/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:33:43 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/04/25 16:41:47 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		total_length;
	char	*result;
	int		counter;

	counter = 0;
	total_length = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = (char *)malloc(total_length * sizeof(char));
	if (!result)
		return (0);
	while (*s1)
	{
		result[counter] = *s1;
		counter++;
		s1++;
	}
	while (*s2)
	{
		result[counter] = *s2;
		counter++;
		s2++;
	}
	result[counter] = 0;
	return (result);
}
