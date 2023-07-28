/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_end_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:22:16 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/28 12:26:58 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_fd(t_fd *fd)
{
	fd->pipe[0] = -2;
	fd->pipe[1] = -2;
	fd->redirection[0] = -2;
	fd->redirection[1] = -2;
	fd->out = -2;
}

void	ft_final_fd(t_fd *fd)
{
	if (fd->pipe[1] != -2)
		fd->out = fd->pipe[1];
	if (fd->redirection[OUT] != -2)
	{
		if (fd->pipe[1] != -2)
			close(fd->pipe[1]);
		fd->out = fd->redirection[OUT];
	}
	if (fd->redirection[IN] != -2)
	{
		if (fd->in != -2)
			close(fd->in);
		fd->in = fd->redirection[IN];
	}
}
