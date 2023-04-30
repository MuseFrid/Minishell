/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 04:31:21 by aabda             #+#    #+#             */
/*   Updated: 2023/04/30 05:36:12 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	ft_add_node(t_env *current, t_env *new, char *value)
{
	new = malloc(sizeof(t_env));
	if (!new)
		exit(EXIT_FAILURE);		//	need to put the good error handling malloc fail !
	new->index = current->index + 1;
	new->next = NULL;
	new->prev = current;
	current->next = new;
	new->value = value;
}

int	ft_export(t_data *data)
{
	t_env	*current;
	t_env	*new;
	char	*value;

	current = data->env;
	// value = 						need to put the good string in the struct
	if (!current)
		return (1);		//	need to put the good error handling if the linked list doesn't exist !
	new = NULL;
	while (current->next)
		current = current->next;
	ft_add_node(current, new, value);
	return (0);
}
