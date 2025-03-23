/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:16:25 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/23 20:06:03 by mbutuzov         ###   ########.fr       */
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
	printf("\n");
	
	ft_putstr_fd("$ ", STDERR);
//	ft_putstr_fd("parent sigint handler\n", STDERR);
	
}

// TODO: continue figuring out correct behaviour of a child process wth signal
void handle_sigint_parent_command(int code)
{
	(void)code;
//	ft_putendl_fd("\n", 2);
//	ft_putstr_fd("$ ", STDERR);
//	ft_putstr_fd("parent sigint handler\n", STDERR);
	
}
/*
//ctrl+\/
void handle_sigquit(int code)
{

	(void)code;
	// char *err_code;

	signal(SIGQUIT, SIG_IGN);
	// err_code = ft_itoa(code);

//	g_sig.sigquit = 1;
}

//ctrl+\/
void set_sigquit(t_sigaction new_action)
{
	//static t_sigaction reserved_action;
	sigaction(SIGQUIT, &new_action, 0);
	
// sigaction
//	signal(SIGQUIT, SIG_IGN);
}


*/
// TODO: figure out sigaddset
//int set_signal(int signum, t_sigaction action)
int set_signal(int signum, void (*handler_func)(int))
{
//	int emptyset_return;
	t_sigaction action;

//	ft_bzero(&action, sizeof(t_sigaction));
	ft_bzero(&action.sa_mask, sizeof(action.sa_mask));
	ft_bzero(&action.sa_flags, sizeof(action.sa_flags));
	action.sa_handler = handler_func;
//	emptyset_return = sigemptyset(&action.sa_mask);
//	if (emptyset_return)
//		return (-1);
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
//	signal(SIGINT, SIG_IGN);
	//signal(SIGINT, SIG_IGN);
	if (set_signal(SIGINT, handle_sigint_parent_command))
		ft_putstr_fd("set signal error\n", 2);
	signal(SIGQUIT, SIG_IGN);
}


void before_heredoc_process_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void child_quit_beh(int asd)
{
	(void)asd;
	//ft_putstr_fd("c q b\n", 2);
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
	/*t_sigaction quit_action;
	t_sigaction int_action;

	ft_bzero(&quit_action, sizeof(t_sigaction));
	ft_bzero(&int_action, sizeof(t_sigaction));
	quit_action.sa_handler = &child_quit_beh;
	int_action.sa_handler = &child_int_beh;
*/
	//set_signal(SIGQUIT, quit_action);
//	set_signal(SIGINT, int_action);
//	ft_putstr_fd("in child, setting signal", 2);
	restore_signal(SIGQUIT);
	restore_signal(SIGINT);
/*
	if (set_signal(SIGQUIT, child_quit_beh))
		ft_putstr_fd("set signal error\n", 2);
	if (set_signal(SIGINT, child_int_beh))
		ft_putstr_fd("set signal error\n", 2);
*/
}

void set_heredoc_signal(void)
{
/*	t_sigaction quit_action;
	t_sigaction int_action;

	ft_bzero(&quit_action, sizeof(t_sigaction));
	ft_bzero(&int_action, sizeof(t_sigaction));
	quit_action.sa_handler = SIG_IGN;
	int_action.sa_handler = &child_int_beh;
*/
//	set_signal(SIGQUIT, quit_action);
//	set_signal(SIGINT, int_action);
	set_signal(SIGQUIT, SIG_IGN);
	set_signal(SIGINT, heredoc_int_beh);
}

/*
void sigquit_child_handler()
{
	exit(131);
}
*/

//ctrl+\/
/*
int set_sigquit_child()
{
	t_sigaction action;

	ft_bzero(&action, sizeof(t_sigaction));
	action.sa_handler = &sigquit_child_handler;
	return (set_signal(SIGQUIT, action));
}
int set_sigquit_child()
{
	t_sigaction action;

	return (restore_signal(SIGQUIT));
*/
/*
	ft_bzero(&action, sizeof(t_sigaction));
	action.sa_handler = &sigquit_child_handler;
	return (set_signal(SIGQUIT, action));
}
*/

/*
void init_sig(void)
{
	sigaction
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	// g_sig.pid = 0;
	// g_sig.exit_status = 0;
}
*/
