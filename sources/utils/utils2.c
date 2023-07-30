/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:23:37 by aabda             #+#    #+#             */
/*   Updated: 2023/07/29 18:19:10 by gduchesn         ###   ########.fr       */
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

char	*ft_strldup(const char *str, int len)
{
	char	*new;
	int		i;
	int		size_str;

	i = 0;
	if (!str)
		return (NULL);
	size_str = ft_strlen(str);
	if (size_str > len)
		size_str = len;
	new = (char *)malloc(sizeof(char) * (size_str + 1));
	if (!new)
		kill_mini("Minishell");
	while (i < len && str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = 0;
	return (new);
}
