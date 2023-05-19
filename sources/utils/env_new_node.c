/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_new_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 22:57:53 by aabda             #+#    #+#             */
/*   Updated: 2023/05/19 05:12:30 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_key_value(t_env *new, char *value)
{
	char	*key;
	char	*val;

	key = ft_catch_key_env(value);
	val = ft_catch_value_env(value);
	new->key = key;
	new->value = val;
}

static void	ft_fill_values(t_env *current, t_env *new, char *value)
{
	new = malloc(sizeof(t_env));
	if (!new)
		exit(EXIT_FAILURE);		//	need to put the good error handling malloc fail !
	new->index = current->index + 1;
	ft_key_value(new, value);
	new->next = NULL;
	new->prev = current;
	current->next = new;
}

void	ft_new_node_env(t_data *data, t_env *current, t_env *new, char *val)
{
	int	i;
	int	equal_index;

	i = -1;
	equal_index = 0;
	while (val[++i])
	{
		if (val[i] == '=')
		{
			if (val[i - 1] == '+')
			{
				equal_index = i;
				ft_concat_env(data, new, val, equal_index);
				break ;
			}
			ft_fill_values(current, new, val);
		}
	}
}
