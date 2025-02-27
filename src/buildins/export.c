/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:45:10 by chlee2            #+#    #+#             */
/*   Updated: 2025/02/27 10:42:25 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void add_key_value_pair(t_key_value **head, const char *key, const char *value)
{
	t_key_value *new_node;
	t_key_value *current;

	current = *head;
	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return;
		}
		current = current->next;
	}

	new_node = malloc(sizeof(t_key_value));
	if (!new_node)
	{
		printf("new_node malloc failed at add_key_value_pair()\n");
		return;
	}

	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = *head;
	*head = new_node;
}

// int key_exists_in_env(t_shell *shell, char *input)
// {
// 	int i;
// 	char *key;

// 	key = ft_strjoin(input, "=");
// 	i = 0;
// 	while (shell->envp[i])
// 	{
// 		if (ft_strstr(shell->envp[i], key))
// 		{
// 			printf("yes\n");
// 			return (i);
// 		}
// 		i++;
// 	}
// 	printf("no\n");
// 	return (-1);
// }

t_key_value *arr_to_key_value(t_shell *shell)
{
    t_key_value *head = NULL;
    t_key_value *new_node;
    char *delimiter;
    int i = 0;

    while (shell->envp[i])
    {
        new_node = malloc(sizeof(t_key_value));
        if (!new_node)
        {
            printf("malloc failed at arr_to_key_value()\n");
            return NULL;
        }
        delimiter = strchr(shell->envp[i], '=');
        if (delimiter)
        {
            *delimiter = '\0';
            new_node->key = ft_strdup(shell->envp[i]);
            new_node->value = ft_strdup(delimiter + 1);
            *delimiter = '=';
        }
        // else
        // {
        //     new_node->key = ft_strdup(shell->envp[i]);
        //     new_node->value = NULL;
        // }
        new_node->next = head;
        head = new_node;
        i++;
    }

    return head;
}

// void free_key_value_list(t_key_value *head)
// {
//     t_key_value *temp;
//     while (head)
//     {
//         temp = head;
//         head = head->next;
//         free(temp->key);
//         free(temp->value);
//         free(temp);
//     }
// }

void from_pair_to_arr(t_shell *shell)
{
	t_key_value *temp;
	int count;
	int i;

	count = 0;
	temp = shell->envp_value_pair;
	while (temp)
    {
        count++;
        temp = temp->next;
    }
	// printf("count: %d\n", count);
	// if (shell->envp)
    // {
    //     for (int i = 0; shell->envp[i]; i++)
    //         free(shell->envp[i]);
    //     free(shell->envp);
    // }
    // shell->envp = malloc(sizeof(char *) * (count + 1));
    // if (!shell->envp)
    // {
    //     printf("malloc failed at update_envp_from_list()\n");
    //     return;
    // }

    temp = shell->envp_value_pair;
	i = 0;
	while (temp)
	{
        // shell->envp[i] = malloc(ft_strlen(temp->key) + ft_strlen(temp->value) + 2);
        // if (!shell->envp[i])
        // {
        //     printf("malloc failed for envp[%d]\n", i);
        //     return;
        // }
		shell->envp[i] = ft_strjoin(temp->key, "=");
		shell->envp[i] = ft_strjoin(shell->envp[i], temp->value);
		temp = temp->next;
		i++;
	}
	shell->envp[count] = NULL;
}

void update_value_in_env(t_shell *shell, char *key, char *value)
{
	// t_key_value *envp_value_pair;
	t_key_value *temp;
	t_key_value *new_node;
	// int i;

	shell->envp_value_pair = arr_to_key_value(shell);

	temp = shell->envp_value_pair;
    while (temp)
    {
        if (strcmp(temp->key, key) == 0)
        {
            free(temp->value);
            temp->value = ft_strdup(value);
            return;
        }
        temp = temp->next;
    }
    new_node = malloc(sizeof(t_key_value));
    if (!new_node)
    {
        printf("malloc failed at update_value_in_env()\n");
        return;
    }
    new_node->key = ft_strdup(key);
    new_node->value = ft_strdup(value);
    new_node->next = shell->envp_value_pair;
	shell->envp_value_pair = new_node;

	// //temp
	// printf("\nUpdated Environment Variables:\n");
    // temp = shell->envp_value_pair;
	// i = 0;
	// while (temp)
	// {
    //     printf("i: %d, %s=%s\n", i, temp->key, temp->value);
    //     temp = temp->next;
	// 	i++;
	// }

	from_pair_to_arr(shell);
}

void handle_export(t_shell *shell) //two loops //first check which token contains =, second check where export is
{
	int i;
	int j;
	char **key_value_pair;
	t_key_value *head;
	// t_key_value *temp;

	head = NULL;
	i = 0;
	key_value_pair = NULL;
	while (shell->tokens[i])
	{
		if (ft_strchar(shell->tokens[i], '='))
		{
			key_value_pair = ft_split(shell->tokens[i], '=');
			if (key_value_pair)
                add_key_value_pair(&head, key_value_pair[0], key_value_pair[1]);
		}
		i++;
	}
	// temp = head;
    // while (temp)
    // {
    //     printf("Key: %s, Value: %s\n", temp->key, temp->value);
    //     temp = temp->next;
    // }

	i = 0;
	while(shell->tokens[i]) //two main cases, 1: already exits key 2: otherwise
	{
		if (strcmp(shell->tokens[i], "export") == 0)
		{
			j = i + 1;
			if (!shell->tokens[j]) //if no second arg follow up by export
				print_tokens(shell->envp);
			while (shell->tokens[j])
			{
				char *that_key = strchr(shell->tokens[j], '='); //x=2
				if (that_key)
					*that_key = '\0';
				else
					return;

				// printf("shell->tokens[j]: %s\n", shell->tokens[j]);
				update_value_in_env(shell, shell->tokens[j], that_key + 1);
				j++;
			}
        }
		i++;
	}

// free_key_value_list(head)

	// int z;
	// z = 0;
	// while (shell->envp[z])
	// {
	// 	printf("shell->envp[%d]: %s\n", z, shell->envp[z]);
	// 	z++;
	// }
}
