/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:34:11 by aabda             #+#    #+#             */
/*   Updated: 2023/06/14 16:48:32 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_builtins_tab(char *cmd)
{
	static char	*tab[] = {
		"cd",
		"echo",
		"env",
		"exit",
		"export",
		"pwd",
		"unset",
		NULL
	};
	int			i;

	i = 0;
	while (tab[i])
	{
		if (strncmp(cmd, tab[i], ft_strlen(cmd)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_check_builtins(t_data *data)
{
	int	(*builtin[8])(t_data *);
	int	res;

	builtin[0] = &ft_cd;
	builtin[1] = &ft_echo;
	builtin[2] = &ft_env;
	builtin[3] = &ft_exit;
	builtin[4] = &ft_export;
	builtin[5] = &ft_pwd;
	builtin[6] = &ft_unset;
	builtin[7] = NULL;
	if (!data->cmds)
		return (0);
	if (!data->cmds->tab)
	{
		data->cmds->builtin = NULL;
		return (0);
	}
	res = ft_builtins_tab(data->cmds->tab[0]);
	if (res < 0)
		data->cmds->builtin = NULL;
	else
		data->cmds->builtin = builtin[res];
	return (0);
}
