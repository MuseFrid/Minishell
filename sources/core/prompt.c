/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:45:18 by aabda             #+#    #+#             */
/*   Updated: 2023/06/28 14:48:45 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_prompt(t_data *data)
{
	char	*path_and_username;
	char	*str;

	path_and_username = ft_path_and_username(data);
	str = readline(path_and_username);
	if (!str)
		ft_exit(data);
	errno = 0;
	return (str);
}
