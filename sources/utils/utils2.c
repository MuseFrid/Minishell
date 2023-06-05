/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:23:37 by aabda             #+#    #+#             */
/*   Updated: 2023/06/04 23:48:35 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp_strict(const char *s1, const char *s2)
{
	int	len_s1;
	int	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (len_s1 == len_s2 && ft_strncmp(s1, s2, len_s1) == 0)
		return (0);
	return (1);
}

char	*ft_get_value_env(t_data *data, char *key)
{
	t_env	*current;

	current = data->env;
	if (!current || !key)
		return (NULL);		// call the error function
	while (current)
	{
		if (ft_strcmp_strict(current->key, key) == 0)
			break ;
		current = current->next;
	}
	if (!current)
		return (NULL);
	return (current->value);
}

int	ft_count_slash(char *str)
{
	int	i;
	int	count;

	if (!str)
		return (0);
	count = 0;
	i = -1;
	while (str[++i])
		if (str[i] == '/')
			++count;
	return (count);
}
