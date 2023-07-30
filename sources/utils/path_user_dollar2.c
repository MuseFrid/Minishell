/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_user_dollar2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:53:23 by aabda             #+#    #+#             */
/*   Updated: 2023/07/30 18:52:45 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_join_pwd_user_dollar(char *user, char *pwd, char *res)
{
	int	i;
	int	j;

	i = -1;
	while (pwd[++i])
		res[i] = pwd[i];
	res[i] = ' ';
	++i;
	j = -1;
	while (user[++j])
	{
		res[i] = user[j];
		++i;
	}
	res[i] = '$';
	res[i + 1] = ' ';
	res[i + 2] = '\0';
}
