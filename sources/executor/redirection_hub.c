/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_hub.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:05:18 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/28 13:48:36 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_outfile(t_simple_cmds *cmds,
	int fd[2], int pick, char *file_to_open)
{
	if (fd[OUT] != -2)
		close(fd[OUT]);
	if (pick == D_GREATER)
		fd[OUT] = open(file_to_open, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd[OUT] = open(file_to_open, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd[OUT] == -1)
	{
		cmds_is_finish(cmds);
		fd[OUT] = -2;
	}
}

void	open_infile(t_simple_cmds *cmds,
	int *which, int pick, char *file_to_open)
{
	if (*which != -2 && *which != -3)
		close(*which);
	if (pick == D_LOWER)
		*which = -3;
	if (pick == LOWER)
		*which = open(file_to_open, O_RDONLY);
	if (*which == -1)
	{
		cmds_is_finish(cmds);
		*which = -2;
	}
}

void	redirection_hub(t_arg *redirection,
	t_simple_cmds *cmds, t_data *data, int fd[2])
{
	int	which;

	fd[IN] = heredoc_handler(redirection, data, cmds);
	fd[OUT] = -2;
	which = -2;
	while (redirection && cmds->end == 0)
	{
		if (redirection->is_token == D_GREATER
			|| redirection->is_token == GREATER)
			create_outfile(cmds, fd, redirection->is_token, redirection->word);
		else
			open_infile(cmds, &which, redirection->is_token, redirection->word);
		redirection = redirection->next;
	}
	if (which != -3)
	{
		if (fd[IN] != -2)
			close (fd[IN]);
		fd[IN] = which;
	}
}
