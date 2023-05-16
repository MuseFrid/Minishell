/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:24:14 by aabda             #+#    #+#             */
/*   Updated: 2023/05/16 23:30:21 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_replace_value_env(t_env *current, char *value)
{
	int	equal_index;
	int	i;

	equal_index = 0;
	while (value[equal_index] != '=')
		equal_index++;
	free(current->value);
	current->value = malloc(sizeof(char *) * \
		(ft_strlen(value) - equal_index) + 1);
	if (!current->value)
		exit(EXIT_FAILURE);		//	need to put the error function
	i = -1;
	while (++i < ft_strlen(value) && value[equal_index])
	{
		current->value[i] = value[equal_index + 1];
		equal_index++;
	}
	current->value[i] = '\0';
}
