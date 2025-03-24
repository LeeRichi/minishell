/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:16:25 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/24 19:58:40 by mbutuzov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//to handle ctrl+c //display a new lie
/*
	signal behaviour
	heredoc:
	normal child process:
	ctrl-c - exit code 130, 
	ctrl-\ - 
	ctrl-d - 
	parent:
*/

//ctrl+c
void handle_sigint(int code)
{
	(void)code;
	ft_putstr_fd("\n", STDERR);
	rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
}

int set_signal(int signum, void (*handler_func)(int))
{
	t_sigaction action;

	ft_bzero(&action.sa_mask, sizeof(action.sa_mask));
	ft_bzero(&action.sa_flags, sizeof(action.sa_flags));
	action.sa_handler = handler_func;
	return (sigaction(signum, &action, 0));
}

int restore_signal(int signum)
{
	t_sigaction action;
	int emptyset_return;

	ft_bzero(&action, sizeof(t_sigaction));
	action.sa_handler = SIG_DFL;
	emptyset_return = sigemptyset(&action.sa_mask);
	if (emptyset_return)
		return (-1);
	return (sigaction(signum, &action, 0));
}

void set_minishell_signal(void)
{
	if (set_signal(SIGQUIT, SIG_IGN))
		ft_putstr_fd("set signal error\n", 2);
		
	if (set_signal(SIGINT, handle_sigint))
		ft_putstr_fd("set signal error\n", 2);
}

void before_child_process_signal(void)
{
//	if (set_signal(SIGINT, handle_sigint_parent_command))
//		ft_putstr_fd("set signal error\n", 2);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}


void before_heredoc_process_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void child_quit_beh(int asd)
{
	(void)asd;
	exit(131);
}
void heredoc_int_beh(int asd)
{
	(void)asd;
	g_sig = 1;
	if (close(0) == -1)
		perror("Can't close heredoc standard input");
}

void set_child_signal(void)
{
	restore_signal(SIGQUIT);
	restore_signal(SIGINT);
}

void set_heredoc_signal(void)
{
	set_signal(SIGQUIT, SIG_IGN);
	set_signal(SIGINT, heredoc_int_beh);
}
