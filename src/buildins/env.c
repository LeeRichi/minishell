/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:45:07 by chlee2            #+#    #+#             */
/*   Updated: 2025/02/14 14:48:14 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// dup2(somefd, 1)
// fd = dup(1)
// redir logic
// dup2(fd, 1)

void handle_env(char **envp)
{
    char **env = envp;
    
    print_tokens(env);
}

