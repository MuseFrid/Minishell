/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 23:05:56 by aabda             #+#    #+#             */
/*   Updated: 2023/05/12 19:25:25 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_logic(t_data *data, t_env *current, char **value)
{
	int	i;

	i = 1;
	while (current && i < current->index)
	{
		if (ft_strncmp(value[i], current->key, ft_strlen(value[i])) == 0)
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
			free(current->key);
			free(current->value);
			free(current);
			break ;
		}
		current = current->next;
		i++;
	}
}

int	ft_unset(t_data *data)
{
	t_env	*current;
	char	**value;

	current = data->env;
	value = data->cmds->str;
	if (!current)
		return (1);
	ft_logic(data, current, value);
	return (0);
}
