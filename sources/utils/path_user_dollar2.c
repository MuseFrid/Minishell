/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_user_dollar2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:53:23 by aabda             #+#    #+#             */
/*   Updated: 2023/05/31 19:08:02 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_catch_home_by_dir(char *str)
{
	int		count_slash;
	int		len_home;
	int		i;
	char	*res;

	str = getcwd(NULL, 0);
	count_slash = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '/')
			++count_slash;
		if (count_slash == 3)
			break ;
	}
	res = malloc(sizeof(char) * i + 1);
	if (!res)
		exit(EXIT_FAILURE);		// call error function
	len_home = i;
	i = -1;
	while (++i < len_home)
		res[i] = str[i];
	res[i] = '\0';
	ft_free((void **)&str);
	return (res);
}

static char	*ft_get_username_by_dir(char *str)
{
	int		first_slash;
	int		last_slash;
	int		i;
	char	*res;

	str = getcwd(NULL, 0);
	first_slash = 1;
	while (str[first_slash] != '/')
		++first_slash;
	last_slash = first_slash + 1;
	while (str[last_slash] != '/')
		++last_slash;
	res = malloc(sizeof(char) * last_slash - first_slash);
	if (!res)
		exit(EXIT_FAILURE);		// call error function
	i = 0;
	while (first_slash != last_slash - 1)
	{
		res[i] = str[first_slash + 1];
		++i;
		++first_slash;
	}
	res[i] = '\0';
	ft_free((void **)&str);
	return (res);
}

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
		res = ft_get_username_by_dir(res);
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
