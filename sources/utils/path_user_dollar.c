/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_user_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:15:00 by aabda             #+#    #+#             */
/*   Updated: 2023/05/31 11:53:12 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_create_pwd_str(char *home, char *str, char *res)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] == home[i])
		++i;
	res[0] = '~';
	j = 0;
	while (++j < (int)ft_strlen(str) - (int)ft_strlen(home) + 1)
	{
		res[j] = str[i];
		++i;
	}
	res[j] = '\0';
}

static char	*ft_cmp_res(char *res, char *home_str, char *str)
{
	if ((ft_strlen(str) - ft_strlen(home_str) == 0))
	{
		res = malloc(sizeof(char) * 3);
		res[0] = '~';
		res[1] = '/';
		res[2] = '\0';
		return (res);
	}
	else
	{
		res = malloc(sizeof(char) * ft_strlen(str) - ft_strlen(home_str) + 2);
		ft_create_pwd_str(home_str, str, res);
		return (res);
	}
	return (NULL);
}

static char	*ft_catch_home(t_data *data, char *str)
{
	t_env	*home;
	char	*home_str;
	char	*res;

	home = data->env;
	home_str = NULL;
	res = NULL;
	if (!home)
		return (NULL);	//	call the error function
	while (home)
	{
		if (ft_strcmp_strict(home->key, "HOME") == 0)
		{
			home_str = home->value;
			break ;
		}
		home = home->next;
	}
	return (ft_cmp_res(res, home_str, str));
}

static char	*ft_catch_pwd_env(t_data *data)
{
	t_env	*current;
	char	*res;

	current = data->env;
	res = NULL;
	if (!current)
		return (NULL);		//	call the error function
	while (current)
	{
		if (ft_strcmp_strict(current->key, "PWD") == 0)
		{
			res = current->value;
			break ;
		}
		current = current->next;
	}
	if (!res)
		return ("NO_PWD_IN_ENV");
	res = ft_catch_home(data, res);
	return (res);
}

char	*ft_path_and_username(t_data *data)
{
	char	*user;
	char	*pwd;
	char	*res;
	int		len_total;

	user = ft_catch_user_env(data);
	pwd = ft_catch_pwd_env(data);
	len_total = ft_strlen(user) + ft_strlen(pwd) + 3;
	res = malloc(sizeof(char) * len_total + 1);
	if (!user || !pwd || !res)
		return (NULL);		//	Need to put the error function
	ft_join_pwd_user_dollar(user, pwd, res);
	return (res);
}
