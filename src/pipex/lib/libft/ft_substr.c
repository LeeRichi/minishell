/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:21:46 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/04/25 20:55:08 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_populate(char const *s, size_t len, int counter, char *result)
{
	while (s[counter] && (len - counter))
	{
		result[counter] = s[counter];
		counter++;
	}
	result[len] = 0;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	int		counter;

	counter = 0;
	result = 0;
	if (start > ft_strlen(s))
	{
		result = (char *)malloc(sizeof(char));
		if (!result)
			return (0);
		*result = 0;
		return (result);
	}
	s += start;
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (0);
	ft_populate(s, len, counter, result);
	return (result);
}
