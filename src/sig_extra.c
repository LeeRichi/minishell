/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_extra.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutuzov <mbutuzov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:59:40 by mbutuzov          #+#    #+#             */
/*   Updated: 2025/04/11 15:08:08 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	before_heredoc_process_signal(void)
{
	if (set_signal(SIGQUIT, SIG_IGN))
	{
		ft_putstr_fd(SHELL_NAME": set signal error\n", 2);
		return (-1);
	}
	if (set_signal(SIGINT, SIG_IGN))
	{
		ft_putstr_fd(SHELL_NAME": set signal error\n", 2);
		return (-1);
	}
	return (0);
}

void	heredoc_int_beh(int sig)
{
	g_sig = sig;
	if (close(0) == -1)
		perror("Close heredoc standard input error");
}

int	set_child_signal(void)
{
	if (restore_signal(SIGQUIT))
	{
		ft_putstr_fd(SHELL_NAME": set signal error\n", 2);
		return (-1);
	}
	if (restore_signal(SIGINT))
	{
		ft_putstr_fd(SHELL_NAME": set signal error\n", 2);
		return (-1);
	}
	return (0);
}

int	set_heredoc_signal(void)
{
	if (set_signal(SIGQUIT, SIG_IGN))
	{
		ft_putstr_fd(SHELL_NAME": set signal error\n", 2);
		return (-1);
	}
	if (set_signal(SIGINT, heredoc_int_beh))
	{
		ft_putstr_fd(SHELL_NAME": set signal error\n", 2);
		return (-1);
	}
	return (0);
}

int	check_sig(t_check_sig_flag flag)
{
	static int	sig_caught = 0;

	if (flag == SIG_CAUGHT)
		sig_caught = 1;
	else if (flag == SIG_RESET)
		sig_caught = 0;
	return (sig_caught);
}
