/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_new_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 22:57:53 by aabda             #+#    #+#             */
/*   Updated: 2023/05/17 00:18:41 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_fill_key_value(t_env *new, char *value, int equal_index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (value[i])
	{
		if (i < equal_index)
			new->key[i] = value[i];
		else
		{
			new->value[j] = value[i];
			j++;
		}
		i++;
	}
}

static void	ft_key_value(t_env *new, char *value)
{
	int	i;
	int	equal_index;

	i = 0;
	equal_index = 0;
	while (value[i])
	{
		if (!equal_index && value[i] == '=')
			equal_index = i + 1;
		i++;
	}
	new->key = malloc(sizeof(char) * equal_index + 1);
	if (!new->key)
		exit(EXIT_FAILURE);		//	need to put the error function !
	new->key[equal_index] = '\0';
	new->value = malloc(sizeof(char) * (i - equal_index) + 1);
	if (!new->value)
		exit(EXIT_FAILURE);		//	need to put the error function !
	new->value[i - equal_index] = '\0';
	ft_fill_key_value(new, value, equal_index);
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
				ft_concat_env(data, val, equal_index);
				break ;
			}
			new = malloc(sizeof(t_env));
			if (!new)
				exit(EXIT_FAILURE);		//	need to put the good error handling malloc fail !
			new->index = current->index + 1;
			ft_key_value(new, val);
			new->next = NULL;
			new->prev = current;
			current->next = new;
		}
	}
}
