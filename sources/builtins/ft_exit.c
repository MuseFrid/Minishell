/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:18:03 by aabda             #+#    #+#             */
/*   Updated: 2023/08/01 09:13:02 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_error_msg(char *error_msg)
{
	write_error("Minishell: exit: ",
		error_msg, ": numeric argument required\n", NULL);
	exit(2);
}

static void	ft_check_digit(char **tab, int *i)
{
	while (tab[1][*i])
		if (!ft_isdigit(tab[1][(*i)++]))
			exit_error_msg(tab[1]);
}

int	ft_exit(t_data *data)
{
	char	**tab;
	int		i;

	i = 0;
	unlink(HEREDOC_FILE);
	errno = 0;
	if (data->cmds->pid == -2)
		printf("exit\n");
	tab = data->cmds->tab;
	if (tab[1])
	{
		if (tab[2])
			return (write_error("Minishell: exit: too many arguments\n",
					NULL, NULL, NULL));
		while (tab[1][i] && tab[1][i] == ' ')
			++i;
		if (tab[1][i] && (tab[1][i] == '+' || tab[1][i] == '-'))
			++i;
		ft_check_digit(tab, &i);
		i = ft_atoi(tab[1]);
		if (errno == -1)
			exit_error_msg(tab[1]);
		exit(i);
	}
	exit(g_ret_val);
	return (0);
}
