/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:31:37 by aabda             #+#    #+#             */
/*   Updated: 2023/07/26 15:59:06 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_add_value(t_env *pwd, t_env *old_pwd, char *current_path)
{
	if (pwd && old_pwd)
	{
		ft_free((void **)&old_pwd->value);
		old_pwd->value = current_path;
		current_path = getcwd(NULL, 0);
		if (!current_path)
			return (1);		//	call the error function
		ft_free((void **)&pwd->value);
		pwd->value = current_path;
	}
	else
		ft_free((void **)&current_path);
	return (0);
}

static char	*ft_get_home(t_data *data)
{
	t_env	*current;
	char	*res;

	current = data->env;
	res = NULL;
	if (!current)
		return (NULL);		// call the error function
	while (current)
	{
		if (ft_strcmp_strict(current->key, "HOME") == 0)
		{
			res = current->value;
			break ;
		}
		current = current->next;
	}
	if (!res)
		res = ft_catch_home_by_dir(res);
	return (res);
}

static void	ft_error_msg(char *c_path)
{
	write(2, "Minishell: cd: ", 15);
	perror(c_path);
//	printf("cd: %s: No such file or directory\n", c_path);
}

static int	ft_check_val_err(t_env *pwd, t_env *old_pwd, char *cd, char *c_path)
{
	while (pwd)
	{
		if (ft_strcmp_strict(pwd->key, "PWD") == 0)
			break ;
		pwd = pwd->next;
	}
	while (old_pwd)
	{
		if (ft_strcmp_strict(old_pwd->key, "OLDPWD") == 0)
			break ;
		old_pwd = old_pwd->next;
	}
	if (chdir(cd) == -1)
	{
		ft_error_msg(cd);
		return (1);		//	call the error function
	}
	if (ft_add_value(pwd, old_pwd, c_path) != 0)
		return (1);		//	call the error function
	return (0);
}

int	ft_cd(t_data *data)
{
	t_env	*pwd;
	t_env	*old_pwd;
	char	*cd;
	char	*current_path;

	pwd = data->env;
	old_pwd = data->env;
	cd = data->cmds->tab[1];
	if (!cd || !ft_strcmp_strict(cd, "~") || !ft_strcmp_strict(cd, "~/"))
		cd = ft_get_home(data);
	current_path = getcwd(NULL, 0);
	if (!pwd || !old_pwd || !current_path)
		return (1);		//	call the error function
	return (ft_check_val_err(pwd, old_pwd, cd, current_path));
}
