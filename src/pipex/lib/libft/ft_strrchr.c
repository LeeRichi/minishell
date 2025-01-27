/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:34:49 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/05/07 13:59:28 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*a;
	char	*last_occ;
	char	character;

	character = c;
	a = (char *)s;
	last_occ = 0;
	while (*a)
	{
		if (character == *a)
			last_occ = a;
		a++;
	}
	if (character == *a)
		last_occ = a;
	return (last_occ);
}
