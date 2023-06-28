/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 13:41:36 by gduchesn          #+#    #+#             */
/*   Updated: 2023/06/28 14:42:43 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_child(t_data *data)
{
	int	stat;

	while (data->cmds)
	{
		if (data->cmds->pid != -2)
		{
			waitpid(data->cmds->pid, &stat, 0);
			if (WIFSIGNALED(stat))
				ret_val = WTERMSIG(stat);
			else if (WIFEXITED(stat))
				ret_val = WEXITSTATUS(stat);
		}
		data->cmds = data->cmds->next;
	}
}
