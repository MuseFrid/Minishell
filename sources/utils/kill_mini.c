/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:15:44 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/29 15:05:22 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kill_mini(char *error_msg)
{
	perror(error_msg);
	unlink(HEREDOC_FILE);
	exit(EXIT_FAILURE);
}
