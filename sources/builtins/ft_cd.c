/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:31:37 by aabda             #+#    #+#             */
/*   Updated: 2023/08/01 08:44:57 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_home(t_data *data)
{
	t_env	*current;
	char	*res;

	current = data->env;
	res = NULL;
	while (current)
	{
		if (ft_strcmp_strict(current->key, "HOME") == 0)
		{
			res = current->value;
			break ;
		}
		current = current->next;
	}
	return (res);
}

static void	ft_refresh_pwd_oldpwd(t_data *data)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*current_path;

	current_path = getcwd(NULL, 0);
	if (!current_path)
		return ;
	pwd = ft_get_env_node_by_key(data, "PWD");
	oldpwd = ft_get_env_node_by_key(data, "OLDPWD");
	free(data->hidden_env->oldpwd);
	if (pwd && (pwd->value != data->hidden_env->pwd))
		ft_free((void **)&pwd->value);
	if (oldpwd && (oldpwd->value != data->hidden_env->oldpwd))
		ft_free((void **)&oldpwd->value);
	data->hidden_env->oldpwd = ft_strdup(data->hidden_env->pwd);
	if (!data->hidden_env->oldpwd)
		data->hidden_env->oldpwd = ft_strdup("");
	ft_free((void **)&(data->hidden_env->pwd));
	data->hidden_env->pwd = current_path;
	if (!data->hidden_env->pwd)
		data->hidden_env->pwd = ft_strdup("");
	if (pwd)
		pwd->value = data->hidden_env->pwd;
	if (oldpwd)
		oldpwd->value = data->hidden_env->oldpwd;
}

static int	ft_check_val_err(t_data *data, char *cd)
{
	if (chdir(cd) == -1)
	{
		ft_error_msg_cd(cd);
		return (1);
	}
	ft_refresh_pwd_oldpwd(data);
	return (0);
}

int	ft_cd(t_data *data)
{
	char	*cd;
	char	*current_path;

	if (data->cmds->tab[1])
	{
		if (data->cmds->tab[2])
		{
			write(2, "Minishell: cd: too many arguments\n", 34);
			return (1);
		}
	}
	cd = data->cmds->tab[1];
	if (!cd)
		cd = ft_get_home(data);
	current_path = getcwd(NULL, 0);
	if (!current_path)
		return (ft_dir_not_found(data, cd));
	free(current_path);
	return (ft_check_val_err(data, cd));
}
