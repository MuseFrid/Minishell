/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:53:30 by aabda             #+#    #+#             */
/*   Updated: 2023/06/14 17:10:01 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_catch_signal(int sig)
{
	if (sig == SIGINT)		//	CTRL-C
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)		//	ctrl-backslash
	{
		ft_exit(NULL);
	}
}

void	ft_handler_signal(void)
{
	struct sigaction	sa_sig;

	sa_sig.sa_flags = SA_RESTART;
	sa_sig.sa_handler = &ft_catch_signal;

	sigaction(SIGINT, &sa_sig, NULL);
	sigaction(SIGQUIT, &sa_sig, NULL);
	sigaction(EOF, &sa_sig, NULL);
}
