/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:16:25 by chlee2            #+#    #+#             */
/*   Updated: 2025/04/04 16:33:39 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//TODO: check sigaction and sigemptyset fail

void	handle_sigint(int code)
{
	(void)code;
	ft_putstr_fd("\n", STDERR);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	set_signal(int signum, void (*handler_func)(int))
{
	struct sigaction	action;
	int					emptyset_return;

	emptyset_return = sigemptyset(&action.sa_mask);
	if (emptyset_return)
		return (-1);
	ft_bzero(&action.sa_flags, sizeof(action.sa_flags));
	action.sa_handler = handler_func;
	return (sigaction(signum, &action, 0));
}

int	restore_signal(int signum)
{
	struct sigaction	action;
	int					emptyset_return;

	ft_bzero(&action, sizeof(struct sigaction));
	action.sa_handler = SIG_DFL;
	emptyset_return = sigemptyset(&action.sa_mask);
	if (emptyset_return)
		return (-1);
	return (sigaction(signum, &action, 0));
}

int	set_minishell_signal(void)
{
	if (set_signal(SIGQUIT, SIG_IGN))
	{
		ft_putstr_fd(SHELL_NAME":minishell set signal error\n", 2);
		return (-1);
	}
	if (set_signal(SIGINT, handle_sigint))
	{
		ft_putstr_fd(SHELL_NAME": minishell set signal error\n", 2);
		return (-1);
	}
	return (0);
}

int	before_child_process_signal(void)
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
