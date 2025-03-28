/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_extra.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:59:40 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/03/28 19:00:40 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	before_heredoc_process_signal(void)
{
	set_signal(SIGQUIT, SIG_IGN);
	set_signal(SIGINT, SIG_IGN);
}

void	heredoc_int_beh(int asd)
{
	(void)asd;
	g_sig = 1;
	if (close(0) == -1)
		perror("Can't close heredoc standard input");
}

void	set_child_signal(void)
{
	restore_signal(SIGQUIT);
	restore_signal(SIGINT);
}

void	set_heredoc_signal(void)
{
	set_signal(SIGQUIT, SIG_IGN);
	set_signal(SIGINT, heredoc_int_beh);
}
