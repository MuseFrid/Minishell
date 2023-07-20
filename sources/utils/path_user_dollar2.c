/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_user_dollar2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 00:53:23 by aabda             #+#    #+#             */
/*   Updated: 2023/07/16 19:38:10 by gduchesn         ###   ########.fr       */
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

static void	ft_fill_string(int f_slash, int l_slash, char *str, char *res)
{
	int	i;

	i = 0;
	while (f_slash != l_slash - 1)
	{
		res[i] = str[f_slash + 1];
		++i;
		++f_slash;
	}
	res[i] = '\0';
}

static char	*ft_get_username_by_dir(char *str)
{
	int		first_slash;
	int		last_slash;
	char	*res;

	str = getcwd(NULL, 0);
	if (ft_count_slash(str) <= 2)
		return (NULL);
	first_slash = 1;
	while (str[first_slash] != '/')
		++first_slash;
	last_slash = first_slash + 1;
	while (str[last_slash] != '/')
		++last_slash;
	res = malloc(sizeof(char) * last_slash - first_slash);
	if (!res)
		kill_mini("Minishell : promt_name");
	ft_fill_string(first_slash, last_slash, str, res);
	ft_free((void **)&str);
	return (res);
}

char	*ft_catch_user_env(t_data *data)
{
	char	*res;

	res = ft_get_value_env(data, "USER");
	if (!res)
	{
		res = ft_get_username_by_dir(res);
		if (!res)
		{
			res = \
				ft_strdup("You are so sus why you want to crash our Minishell");
			if (!res)
				kill_mini("Minishell : promt_name");
		}
	}
	return (res);
}

void	ft_join_pwd_user_dollar(char *user, char *pwd, char *res)
{
	int	i;
	int	j;

	i = -1;
	while (pwd[++i])
		res[i] = pwd[i];
	res[i] = ' ';
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
