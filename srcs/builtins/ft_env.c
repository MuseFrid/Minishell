/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:39:36 by aabda             #+#    #+#             */
/*   Updated: 2023/04/29 00:10:32 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_data *data)
{
	t_env	*current;

	current = data->env;
	if (!current)
		return (1);
	while (current)
	{
		printf("%s\n", current->value);
		current = current->next;
	}
	return (0);
}