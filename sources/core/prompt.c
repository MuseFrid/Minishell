/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:45:18 by aabda             #+#    #+#             */
/*   Updated: 2023/07/30 19:13:15 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_prompt(t_data *data)
{
	char	*path_and_username;
	char	*str;

	if (data->nbr_l == INT_MAX)
		data->nbr_l = -1;
	++data->nbr_l;
	path_and_username = ft_path_and_username(data);
	if (path_and_username)
		str = readline(path_and_username);
	else
		str = readline("\033[1m\033[33mMinishell$ \033[0m");
	free(path_and_username);
	if (!str)
		exit(g_ret_val);
	errno = 0;
	return (str);
}
