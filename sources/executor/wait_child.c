/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:41:36 by gduchesn          #+#    #+#             */
/*   Updated: 2023/08/01 01:44:58by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_wtermsig(int sig)
{
	if (sig == 2)
	{
		write(1, "\n", 1);
		g_ret_val = 130;
	}
	if (sig == 3)
	{
		write(1, "Quit: 3\n", 8);
		g_ret_val = 131;
	}
}

void	wait_child(t_data *data)
{
	int				stat;
	t_simple_cmds	*snake;

	snake = data->cmds;
	while (snake)
	{
		if (snake->pid != -2 && snake->pid != -1)
		{
			waitpid(snake->pid, &stat, 0);
			if (WIFSIGNALED(stat))
				child_wtermsig(WTERMSIG(stat));
			else if (WIFEXITED(stat))
				g_ret_val = WEXITSTATUS(stat);
		}
		snake = snake->next;
	}
}
