/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   underscore.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 02:03:35 by aabda             #+#    #+#             */
/*   Updated: 2023/05/29 00:39:56 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_catch_last_arg(char **args)
{
	int		i;

	if (!args)
		return (NULL);
	i = 0;
	while (args[i])
		++i;
	return (args[i - 1]);
}

void	ft_env_underscore(t_data *data)
{
	t_env	*current;
	char	*arg;

	current = data->env;
	arg = ft_catch_last_arg(data->cmds->str);
	if (!current || !arg)
		exit(EXIT_FAILURE);		//	need to put the error function
	while (current)
	{
		if (ft_strcmp_strict(current->key, "_") == 0)
		{
			ft_free((void **)&current->value);
			current->value = arg;
			break ;
		}
		current = current->next;
	}
}