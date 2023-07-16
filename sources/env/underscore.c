/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   underscore.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 02:03:35 by aabda             #+#    #+#             */
/*   Updated: 2023/07/16 15:49:01 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_catch_last_arg(char **args)
{
	int		i;

	if (!args || !args[0])
		return (NULL);
	i = 0;
	while (args[i])
		++i;
	return (args[i - 1]);
}

void	ft_env_underscore(t_data *data)
{
	t_env	*current;
	char	*arg;

	current = data->env;
	if (!current)
		kill_mini("Minishell : env_underscore");
	arg = ft_catch_last_arg(data->cmds->tab);
	if (!arg)
		return ;
	while (current)
	{
		if (ft_strcmp_strict(current->key, "_") == 0)
		{
			ft_free((void **)&current->value);
			current->value = arg;
			break ;
		}
		current = current->next;
	}
}
