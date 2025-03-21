/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:28:12 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/21 20:56:57 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TODO: free before exit
char *str_append(char *str, char c)
{
    size_t len = str ? strlen(str) : 0;
    char *new_str = malloc(len + 2);
    if (!new_str)
    {
        // perror("malloc");
		print_error_message(error_init(MALLOC_FAIL, 0, 0));
        exit(EXIT_FAILURE);
    }
    if (str)
    {
        strcpy(new_str, str);
        free(str);
    }
    new_str[len] = c;
    new_str[len + 1] = '\0';
    return new_str;
}

// char *ft_getenv(char *env_name, char **envp)
// {
		
// }

char *get_env_value(char *env_name, t_shell *shell)
{
	char *env_value;

	env_value = ft_getenv(env_name, shell);
	if (!env_value)
		return (NULL);
		// return ("");
	// return (ft_strdup(env_value));
	return (env_value);
}

int ft_arraylen(char **tokens)
{
	int len;

	len = 0;
	if (!tokens)
		return (0);
	while (tokens[len] != NULL)
        	len++;
	return (len);
}

int ft_start_with(char *str, char c)
{
    int i = 0;

    while (str[i])
    {
        while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        	i++;
        if (str[i] != c)
            return (0);
		else
			return (1);
        i++;
    }
    return (0);
}

char *ft_start_with_specials(char *str) //includes pipe
{
	int i;
	int j;
	size_t len;;
	const char **special_chars;

	special_chars = (const char *[]){">>", "<<", ">", "<", "|", NULL};
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	j = 0;
	while (special_chars[j] != NULL)
	{
		len = strlen(special_chars[j]);
		if (strncmp(&str[i], special_chars[j], len) == 0)
			return ((char *)special_chars[j]);
        j++;
    }

    return NULL;
}


int ft_end_with(char *str, char c)
{
    // int i = 0;
	int len;

	len = ft_strlen(str);
	while (len > 0)
	{
		len--;
		while (str[len] == ' ' || str[len] == '\t' || str[len] == '\n')
			len--;
        if (str[len] == c)
			return (1);
		else
			return (0);
        len--;
    }
    return (0);
}
