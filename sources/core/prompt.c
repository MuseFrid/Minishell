/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:45:18 by aabda             #+#    #+#             */
/*   Updated: 2023/07/28 03:31:19 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_prompt(t_data *data)
{
	char	*path_and_username;
	char	*str;

	if (data->heredoc->nbr_l == INT_MAX)
		data->heredoc->nbr_l = -1;
	++data->heredoc->nbr_l;
	path_and_username = ft_path_and_username(data);
	str = readline(path_and_username);
	free(path_and_username);
	if (!str)
		exit(ret_val);
	errno = 0;
	return (str);
}
