/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_user_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:15:00 by aabda             #+#    #+#             */
/*   Updated: 2023/06/27 17:44:07 by gduchesn         ###   ########.fr       */
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
	if (!home_str)
		home_str = ft_catch_home_by_dir(home_str);
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
	char	*home;
	char	*res;

	res = NULL;
	home = ft_get_value_env(data, "HOME");
	if (!home)
		return (NULL);
	return (ft_cmp_res(res, home, str));
}

static char	*ft_catch_pwd_env(t_data *data)
{
	char	*res;
	char	*home;

	res = getcwd(NULL, 0);
	home = NULL;
	if (!res)
		return (NULL);	//	call error function
	home = ft_get_value_env(data, "HOME");
	if (!home)
		return (res);
	if (ft_strlen(home) < ft_strlen(res))
		res = ft_catch_home(data, res);
	return (res);
}

char	*ft_path_and_username(t_data *data)
{
	char	*user;
	char	*pwd;
	char	*res;
	char	*final;
	int		len_total;

	user = ft_catch_user_env(data);
	pwd = ft_catch_pwd_env(data);
	len_total = ft_strlen(user) + ft_strlen(pwd) + 3;
	res = malloc(sizeof(char) * len_total + 1);
	if (!user || !pwd || !res)
		return (NULL);		//	Need to put the error function
	ft_join_pwd_user_dollar(user, pwd, res);
	final = ft_strjoin(res, RESET);
	free(res);
	if (!final)
		exit(1);
	return (final);
}
