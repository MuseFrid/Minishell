/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 04:31:21 by aabda             #+#    #+#             */
/*   Updated: 2023/07/26 23:18:20 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_key_is_valid(char *key)
{
	int	i;

	if (!key || !key[0])
		return (1);
	i = 1;
	if (!key || !key[0])
		return (1);
	if ((key[0] < 'a' && key[0] > 'z') || (key[0] < 'A' && key[0] > 'Z'))
		return (1);
	while (key && key[i])
	{
		if ((key[i] < 'a' || key[i] > 'z')
			&& (key[i] < 'A' || key[i] > 'Z')
			&& ((key[i] < '0' || key[i] > '9')) && key[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static	int	ft_node(t_data *data, t_env *new, char *val)
{
	t_env	*tmp;
	int		replace;
	char	*key;

	tmp = data->env;
	replace = 0;
	key = ft_catch_key_env(val);
	if (ft_check_key_is_valid(key) != 0)
	{
		write(2, "Minishell: export: `", 20);
		write(2, val, ft_strlen(val));
		write(2, "\': not a valid identifier\n", 26);
		return (1);
	}
	while (tmp)
	{
		if (ft_strcmp_strict(tmp->key, key) == 0 && val[ft_strlen(key)] != '+')
		{
			ft_replace_value_env(tmp, val);
			replace = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (!replace)
		ft_new_node_env(data, new, val);
	ft_free((void **)&key);
	return (0);
}

int	ft_export(t_data *data)
{
	t_env	*new;
	char	**value;
	int		i;

	value = data->cmds->tab;
	if (!value)
		return (1);		//	need to put the good error handling if the linked list doesn't exist !
	new = NULL;
	i = 0;
	while (value[++i])
		if (ft_node(data, new, value[i]) == 1)
			return (1);
	return (0);
}
