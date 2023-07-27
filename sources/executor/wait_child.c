/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:41:36 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/26 20:39:07 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_child(t_data *data)
{
	int				stat;
	t_simple_cmds	*snake;

	snake = data->cmds;
	while (snake)
	{
		if (snake->pid != -2)
		{
			waitpid(snake->pid, &stat, 0);
			if (WIFSIGNALED(stat))
				ret_val = WTERMSIG(stat);
			else if (WIFEXITED(stat))
				ret_val = WEXITSTATUS(stat);
		}
		snake = snake->next;
	}
	ft_handler_signal(0);
}
