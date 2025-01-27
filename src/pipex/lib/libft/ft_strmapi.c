/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:56:03 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/05/02 20:20:41 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	char	*temp;
	size_t	length;

	length = ft_strlen(s);
	result = (char *)malloc((length + 1) * sizeof(char));
	if (!result)
		return (0);
	temp = result;
	while (*s)
	{
		*temp = f(temp - result, *s);
		temp++;
		s++;
	}
	*temp = 0;
	return (result);
}
