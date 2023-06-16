/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:53:30 by aabda             #+#    #+#             */
/*   Updated: 2023/06/16 13:35:30 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_sig_handling(int sig)
{	
	if (sig == SIGINT)		//	CTRL-C
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_handler_signal(void)
{
	struct sigaction	sa_sig;

	sa_sig.sa_flags = SA_RESTART;
	sa_sig.sa_handler = &ft_sig_handling;

	sigaction(SIGINT, &sa_sig, NULL);	//	CTRL-C
	signal(SIGQUIT, SIG_IGN);			//	CTRL-BACKSLASH
	signal(SIGTSTP, SIG_IGN);			//	CTRL-Z
}
