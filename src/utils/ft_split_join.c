/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_join.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:21:13 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/27 14:32:14 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"
#include "../../includes/minishell.h"

static size_t	count_tab_chars(char **tab)
{
	size_t	i;
	size_t	char_count;

	char_count = 0;
	i = 0;
	while (tab[i])
		char_count += ft_strlen(tab[i++]);
	return (char_count);
}

int	write_word(char *text, char *word, size_t char_length)
{
	int		length;
	size_t	word_length;

	word_length = ft_strlen(word);
	length = word_length;
	if (!length)
		return (0);
	while (word_length--)
		text[--char_length] = word[word_length];
	return (length);
}

char	*ft_split_join(char **tab, char *sep)
{
	char	*text;
	char	*word;
	size_t	char_length;
	size_t	word_length;
	size_t	tab_length;

	tab_length = count_split(tab);
	word_length = 0;
	if (sep)
		word_length += ft_strlen(sep);
	char_length = count_tab_chars(tab) + word_length * (tab_length - 1);
	text = ft_calloc(char_length + 1, sizeof (char));
	if (!text)
		return (0);
	while (tab_length--)
	{
		word = tab[tab_length];
		char_length -= write_word(text, word, char_length);
		if (sep && tab_length)
		{
			char_length -= write_word(text, sep, char_length);
		}
	}
	return (text);
}
