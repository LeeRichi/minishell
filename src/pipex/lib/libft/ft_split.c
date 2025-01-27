/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:29:32 by mbutuzov          #+#    #+#             */
/*   Updated: 2024/11/28 20:40:17 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_word_length(const char *s, char c)
{
	int	counter;

	counter = 0;
	while (s[counter] && s[counter] != c)
		counter++;
	return (counter);
}

static const char	*ft_skip_char(const char *s, char c)
{
	while (*s == c && *s)
		s++;
	return (s);
}

static int	count_words(const char *s, char c)
{
	int	length;
	int	counter;

	counter = 0;
	length = -1;
	s = ft_skip_char(s, c);
	while (length)
	{
		length = get_word_length(s, c);
		s += length;
		s = ft_skip_char(s, c);
		counter++;
	}
	return (counter);
}

static int	ft_populate(char **final, const char *s, char c)
{
	int	length;
	int	counter;

	counter = 0;
	length = -1;
	s = ft_skip_char(s, c);
	while (length)
	{
		length = get_word_length(s, c);
		if (length)
		{
			*final = ft_substr(s, 0, length);
			if (!*final)
			{
				while (counter--)
					free(*(final - counter - 1));
				return (0);
			}
			final++;
		}
		s += length;
		s = ft_skip_char(s, c);
		counter++;
	}
	return (counter);
}

char	**ft_split(char const *s, char c)
{
	char	**final;
	int		counter;
	int		result;

	counter = count_words(s, c);
	final = (char **)malloc(sizeof(char *) * (counter));
	if (!final)
		return (0);
	final[counter - 1] = 0;
	result = ft_populate(final, s, c);
	if (!result)
	{
		free(final);
		return (0);
	}
	return (final);
}
