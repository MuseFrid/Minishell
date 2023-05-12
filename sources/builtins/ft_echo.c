/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 05:37:54 by aabda             #+#    #+#             */
/*   Updated: 2023/05/12 17:00:13 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_data *data)
{
	char	**value;
	int		i;

	value = data->cmds->str;
	i = 0;
	while (value[i])
		i++;
	if (i == 3 && ft_strncmp(value[1], "-n", 2) == 0)
		printf("%s", value[2]);
	else if (i == 2)
		printf("%s\n", value[1]);
	else
		printf("\n");
	return (0);
}
