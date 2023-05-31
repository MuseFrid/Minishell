/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_user_dollar2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:53:23 by aabda             #+#    #+#             */
/*   Updated: 2023/05/31 11:53:29 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_catch_user_env(t_data *data)
{
	t_env	*current;
	char	*res;

	current = data->env;
	res = NULL;
	if (!current)
		return (NULL);		//	need to put the error function
	while (current)
	{
		if (ft_strcmp_strict(current->key, "USER") == 0)
		{
			res = current->value;
			break ;
		}
		current = current->next;
	}
	if (!res)
		return ("NO_USER_IN_ENV");
	return (res);
}

void	ft_join_pwd_user_dollar(char *user, char *pwd, char *res)
{
	int	i;
	int	j;

	i = -1;
	while (pwd[++i])
		res[i] = pwd[i];
	res[i] = '\t';
	++i;
	j = -1;
	while (user[++j])
	{
		res[i] = user[j];
		++i;
	}
	res[i] = '$';
	res[i + 1] = ' ';
	res[i + 2] = '\0';
}
