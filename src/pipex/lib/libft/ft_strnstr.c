/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:02:07 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/05/08 14:22:57 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (!*needle)
		return ((char *)haystack);
	while (*haystack && len--)
	{
		if (needle_len <= ft_strlen(haystack) && needle_len <= len + 1)
		{
			if (!ft_strncmp(haystack, needle, ft_strlen(needle)))
				return ((char *)haystack);
		}
		else
			return (0);
		haystack++;
	}
	return (0);
}
