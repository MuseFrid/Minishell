/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 05:37:54 by aabda             #+#    #+#             */
/*   Updated: 2023/07/26 12:18:27 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check(char **value, int i)
{
	if (value[i + 1])
		printf("%s ", value[i]);
	else
		printf("%s", value[i]);
}

static void	ft_logic(char **value, int i)
{
	if (value[1] && ft_strncmp(value[1], "-n", 2) == 0)
	{
		++i;
		while (value[++i])
			ft_check(value, i);
		return ;
	}
	else
		while (value[++i])
			ft_check(value, i);
	printf("\n");
}

int	ft_echo(t_data *data)
{
	char	**value;
	int		i;

	value = data->cmds->tab;
	i = 0;
	ft_logic(value, i);
	return (0);
}
