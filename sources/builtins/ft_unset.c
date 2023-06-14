/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 23:05:56 by aabda             #+#    #+#             */
/*   Updated: 2023/06/14 17:22:45 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_var_found(t_data *data, t_env *current)
{
	if (current == data->env)
	{
		data->env = current->next;
		current->next->prev = NULL;
	}
	else
	{
		current->prev->next = current->next;
		if (current->next)
			current->next->prev = current->prev;
	}
	ft_free((void **)&current->key);
	ft_free((void **)&current->value);
	ft_free((void **)&current);
}

static void	ft_logic(t_data *data, t_env *current, char **value, int i)
{
	t_env	*first;
	char	*key;

	while (value[i])
	{
		key = ft_catch_key_env(value[i]);
		first = data->env;
		current = first;
		while (current)
		{
			if (ft_strcmp_strict(key, current->key) == 0)
			{
				ft_var_found(data, current);
				break ;
			}
			current = current->next;
		}
		ft_free((void **)&key);
		i++;
	}
}

int	ft_unset(t_data *data)
{
	t_env	*current;
	char	**value;
	int		i;

	current = data->env;
	value = data->cmds->tab;
	i = 1;
	if (!current || !value)
		return (1);
	ft_logic(data, current, value, i);
	return (0);
}
