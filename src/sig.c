/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:16:25 by chlee2            #+#    #+#             */
/*   Updated: 2025/03/19 20:51:26 by mbutuzov         ###   ########.fr       */
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
}

//ctrl+\/
void handle_sigquit(int code)
{

	(void)code;
	// char *err_code;

	signal(SIGQUIT, SIG_IGN);
	// err_code = ft_itoa(code);

//	g_sig.sigquit = 1;
}

void set_sigquit_default()
{
	signal(SIGQUIT, SIG_IGN);
}
/*
void set_sigquit_before_child()
{
	
}
*/

void sigquit_child_handler()
{
	exit(131);
}

void set_sigquit_child()
{
	signal(SIGQUIT, &sigquit_child_handler);
//	sigaction
}

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
