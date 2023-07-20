/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:53:30 by aabda             #+#    #+#             */
/*   Updated: 2023/07/19 17:01:53 by gduchesn         ###   ########.fr       */
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
	}
}

static void	ft_sig_heredoc(int sig)
{
	write(1, "\n", 1);
	close(0);
	(void) sig;
}

void	ft_handler_signal(int is_heredoc)
{
	struct sigaction	sa_sig;

	if (is_heredoc)
	{
		sa_sig.sa_handler = &ft_sig_heredoc;
		sigaction(SIGINT, &sa_sig, NULL);
	}
	else
	{
		sa_sig.sa_flags = SA_RESTART;
		sa_sig.sa_handler = &ft_sig_handling;
		sigaction(SIGINT, &sa_sig, NULL);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		ret_val = 130;
	}
}
