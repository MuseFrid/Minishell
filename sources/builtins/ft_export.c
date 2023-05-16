/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 04:31:21 by aabda             #+#    #+#             */
/*   Updated: 2023/05/16 23:12:20 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_node(t_data *data, t_env *current, t_env *new, char *val)
{
	t_env	*tmp;
	int		replace;

	tmp = data->env;
	replace = 0;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, val, ft_strlen(tmp->key)) == 0)
		{
			ft_replace_value_env(tmp, val);
			replace = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (!replace)
		ft_new_node_env(data, current, new, val);
}

int	ft_export(t_data *data)
{
	t_env	*current;
	t_env	*new;
	char	**value;
	int		i;

	current = data->env;
	value = data->cmds->str;
	if (!current)
		return (1);		//	need to put the good error handling if the linked list doesn't exist !
	new = NULL;
	while (current->next)
		current = current->next;
	i = 0;
	while (value[++i])
	{
		ft_node(data, current, new, value[i]);
		current = current->next;
	}
	return (0);
}
