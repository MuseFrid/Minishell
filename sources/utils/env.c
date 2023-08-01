/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 20:24:14 by aabda             #+#    #+#             */
/*   Updated: 2023/08/01 09:29:58 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_catch_value_env(char *value)
{
	int		i;
	int		j;
	int		equal_index;
	char	*str;

	str = NULL;
	equal_index = 0;
	i = -1;
	while (value[++i])
		if (!equal_index && value[i] == '=')
			equal_index = i;
	if (!equal_index)
		return (NULL);
	str = malloc(sizeof(char) * (i - equal_index + 1));
	if (!str)
		kill_mini("Minishell");
	j = 0;
	while (++equal_index < i)
	{
		str[j] = value[equal_index];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_catch_key_env(char *value)
{
	int		i;
	int		equal_index;
	char	*key;

	key = NULL;
	i = 0;
	equal_index = 0;
	while (value[i])
	{
		if (value[i] == '+' && value[i + 1] == '=')
			break ;
		if (value[i] == '=')
			break ;
		equal_index++;
		i++;
	}
	key = malloc(sizeof(char) * equal_index + 1);
	if (!key)
		kill_mini("Minishell");
	i = -1;
	while (++i < equal_index)
		key[i] = value[i];
	key[i] = '\0';
	return (key);
}

void	ft_replace_value_env(t_env *current, char *value)
{
	char	*new_val;

	new_val = ft_catch_value_env(value);
	if (!new_val)
		return ;
	ft_free((void **)&current->value);
	current->value = new_val;
}

t_env	*ft_last_elem_env(t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current->next)
		current = current->next;
	return (current);
}
