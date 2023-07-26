/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:53:30 by aabda             #+#    #+#             */
/*   Updated: 2023/07/26 16:26:54 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_sig_handling(int sig)
{	
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ret_val = 130;
	}
}

static void	ft_sig_heredoc(int sig)
{
	write(1, "\n", 1);
	close(0);
	ret_val = 130;
	(void) sig;
}

void	ft_handler_signal(int pick)
{
	struct sigaction	sa_sig;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	if (pick == 1)
	{
		sa_sig.sa_handler = &ft_sig_heredoc;
		sigaction(SIGINT, &sa_sig, NULL);
	}
	else if (pick == 2)
		signal(SIGINT, SIG_IGN);
	else
	{
		sa_sig.sa_flags = SA_RESTART;
		sa_sig.sa_handler = &ft_sig_handling;
		sigaction(SIGINT, &sa_sig, NULL);
	}
}
