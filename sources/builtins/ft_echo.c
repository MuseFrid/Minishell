/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 05:37:54 by aabda             #+#    #+#             */
/*   Updated: 2023/07/30 19:16:24 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_logic(char **args)
{
	int	i;
	int	j;
	int	check;

	i = 1;
	check = 0;
	while (args && args[i] && args[i][0] == '-')
	{
		j = 0;
		while (args[i][++j] && args[i][j] == 'n')
			;
		if (args[i][j] && args[i][j] != 'n')
			break ;
		check = 1;
		++i;
	}
	while (args && args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		++i;
	}
	if (!check)
		printf("\n");
}

int	ft_echo(t_data *data)
{
	char	**value;

	value = data->cmds->tab;
	ft_logic(value);
	return (0);
}
