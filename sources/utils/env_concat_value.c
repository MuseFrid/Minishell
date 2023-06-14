/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_concat_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 23:09:19 by aabda             #+#    #+#             */
/*   Updated: 2023/05/31 17:07:17 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_create(t_data *data, t_env *new, char *value)
{
	t_env	*current;
	char	*key;
	char	*val;

	new = malloc(sizeof(t_env));
	if (!new)
		exit(EXIT_FAILURE);		//	need to call the error function
	current = data->env;
	while (current->next)
		current = current->next;
	key = ft_catch_key_env(value);
	val = ft_catch_value_env(value);
	new->key = key;
	new->value = val;
	new->next = NULL;
	new->prev = current;
	current->next = new;
}

static void	ft_logic(t_env *current, char *value, int equal_index)
{
	char	*str;
	int		i;
	int		len_total;

	len_total = (ft_strlen(value) - equal_index) + \
		ft_strlen(current->value);
	str = malloc(sizeof(char *) * len_total + 1);
	if (!str)
		exit(EXIT_FAILURE);		//	need to call the error function
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
	ft_free((void **)&current->value);
	current->value = str;
}

void	ft_concat_env(t_data *data, t_env *new, char *value, int equal_index)
{
	t_env	*current;
	char	*key;
	int		check;

	current = data->env;
	key = ft_catch_key_env(value);
	check = 0;
	while (current)
	{
		if (ft_cmp_str_strict(current->key, key) == 0)
		{
			ft_free((void **)&key);
			check = 1;
			ft_logic(current, value, equal_index);
		}
		current = current->next;
	}
	if (!check)
		ft_create(data, new, value);
}
