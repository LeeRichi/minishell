/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:02:27 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/28 19:04:25 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_pwd(char **custom, t_shell *shell, char *cwd, char *path)
{
	char	*temp;

	cwd = getcwd(path, PATH_MAX);
	if (!cwd)
		return (cwd_fail(shell, custom));
	temp = ft_strjoin(custom[0], cwd);
	if (!temp)
	{
		free_matrix(custom);
		malloc_fail_clean_exit(shell);
	}
	free(custom[0]);
	custom[0] = temp;
	custom[2] = NULL;
	return (0);
}
