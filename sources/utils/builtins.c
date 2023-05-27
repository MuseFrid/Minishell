/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:34:11 by aabda             #+#    #+#             */
/*   Updated: 2023/05/27 22:07:11 by aabda            ###   ########.fr       */
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
	int	argc;

	builtin[0] = &ft_cd;
	builtin[1] = &ft_echo;
	builtin[2] = &ft_env;
	builtin[3] = &ft_exit;
	builtin[4] = &ft_export;
	builtin[5] = &ft_pwd;
	builtin[6] = &ft_unset;
	builtin[7] = NULL;
	res = ft_builtins_tab(data->cmds->str[0]);
	argc = 0;
	while (data->cmds->str[argc])
		++argc;
	if (res < 0)
		data->cmds->builtin = NULL;
	else if (argc == 1 && ft_strcmp_strict(data->cmds->str[0], "export") == 0)
		data->cmds->builtin = builtin[2];
	else
		data->cmds->builtin = builtin[res];
	return (0);
}
