/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ga_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:26:35 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/25 17:23:19 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ga_error(char *error_msg)
{
	write (2, RED, ft_strlen(RED));
	write (2, error_msg, ft_strlen(error_msg));
	write (2, RESET, ft_strlen(RESET));
	return (FAIL);
}

void	cmds_is_finish(t_simple_cmds *cmds)
{
	if (cmds->end == 0)
		perror("Minishell");
	cmds->end = 1;
	ret_val = 1;
}
