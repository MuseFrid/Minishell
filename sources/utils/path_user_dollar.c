/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_user_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:42:47 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/31 18:42:48 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_catch_pwd_env(t_data *data)
{
	char	*res;
	char	*home;

	home = NULL;
	res = getcwd(NULL, 0);
	if (!res)
		return (NULL);
	home = ft_strdup(ft_get_value_env(data, "HOME"));
	if (!home)
		return (res);
	free(home);
	return (res);
}

char	*ft_path_and_username(t_data *data)
{
	char	*user;
	char	*pwd;
	char	*res;
	char	*final;

	user = ft_strdup(ft_get_value_env(data, "USER"));
	pwd = ft_catch_pwd_env(data);
	if (!user || !pwd)
	{
		free(user);
		free(pwd);
		return (NULL);
	}
	res = malloc(sizeof(char) * ft_strlen(user) + ft_strlen(pwd) + 4);
	if (!res)
		kill_mini("Minishell : promt_name");
	ft_join_pwd_user_dollar(user, pwd, res);
	free(pwd);
	free(user);
	final = ft_strjoin(res, RESET);
	free(res);
	res = ft_strjoin(BOLDYELLOW, final);
	free(final);
	return (res);
}
