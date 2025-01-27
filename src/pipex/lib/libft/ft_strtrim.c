/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:45:59 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/12/10 13:02:14 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*temp_set;
	const char	*temp_s1;

	temp_set = set;
	while (*s1)
	{
		temp_set = ft_strchr(set, *s1);
		if (!temp_set)
			break ;
		s1++;
	}
	temp_s1 = s1;
	s1 += ft_strlen(s1);
	while (s1 > temp_s1)
	{
		temp_set = ft_strchr(set, *s1);
		if (!temp_set)
			break ;
		s1--;
	}
	return (ft_substr(temp_s1, 0, s1 - temp_s1 + 1));
}
