/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_concat_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 23:09:19 by aabda             #+#    #+#             */
/*   Updated: 2023/05/17 00:16:48 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_logic(t_env *current, char *value, int equal_index)
{
	char	*str;
	int		i;
	int		len_total;

	len_total = (ft_strlen(value) - equal_index) + \
		ft_strlen(current->value);
	str = malloc(sizeof(char *) * len_total + 1);
	if (!str)
		exit(EXIT_FAILURE);		//	need to put error function
	i = -1;
	while (current->value[++i])
		str[i] = current->value[i];
	while (i < len_total)
	{
		str[i] = value[equal_index + 1];
		i++;
		equal_index++;
	}
	str[i] = '\0';
	free(current->value);
	current->value = str;
}

void	ft_concat_env(t_data *data, char *value, int equal_index)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		if (ft_strncmp(current->key, value, ft_strlen(current->key) - 1) == 0)
			ft_logic(current, value, equal_index);
		current = current->next;
	}
}
