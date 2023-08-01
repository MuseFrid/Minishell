/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:34:11 by aabda             #+#    #+#             */
/*   Updated: 2023/08/01 10:17:12 by aabda            ###   ########.fr       */
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
		if (ft_strcmp_strict(cmd, tab[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	cmds_tab_value(t_simple_cmds *cmds)
{
	if (!cmds)
		return (1);
	if (!cmds->tab)
		return (1);
	return (0);
}

int	ft_check_builtins(t_simple_cmds *cmds)
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
	if (cmds_tab_value(cmds))
		return (0);
	res = ft_builtins_tab(cmds->tab[0]);
	argc = 0;
	while (cmds->tab[argc])
		++argc;
	if (res < 0)
		cmds->builtin = NULL;
	else if (argc == 1 && ft_strcmp_strict(cmds->tab[0], "export") == 0)
		cmds->builtin = builtin[2];
	else
		cmds->builtin = builtin[res];
	return (0);
}
