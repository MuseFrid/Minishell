/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ga_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:26:35 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/29 19:34:42 by gduchesn         ###   ########.fr       */
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

int	write_error(char *prt1, char *prt2, char *prt3, char *prt4)
{
	if (prt1)
		write(2, prt1, ft_strlen(prt1));
	if (prt2)
		write(2, prt2, ft_strlen(prt2));
	if (prt3)
		write(2, prt3, ft_strlen(prt3));
	if (prt4)
		write(2, prt4, ft_strlen(prt4));
	return (1);
}

void	cmds_is_finish(t_simple_cmds *cmds)
{
	if (cmds->end == 0)
		perror("Minishell");
	cmds->end = 1;
	g_ret_val = 1;
}
