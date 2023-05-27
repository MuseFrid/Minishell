/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:31:37 by aabda             #+#    #+#             */
/*   Updated: 2023/05/27 19:45:36 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_add_value(t_env *pwd, t_env *old_pwd, char *current_path)
{
	ft_free((void **)&old_pwd->value);
	old_pwd->value = current_path;
	current_path = getcwd(NULL, 0);
	if (!current_path)
		return (1);		//	call the error function
	ft_free((void **)&pwd->value);
	pwd->value = current_path;
	return (0);
}

static void	ft_error_msg(t_env *pwd, t_env *old_pwd, char *cd, char *c_path)
{
	(void)pwd;
	(void)old_pwd;
	(void)cd;
	free(c_path);
	printf("%s\n", c_path);
}

int	ft_cd(t_data *data)
{
	t_env	*pwd;
	t_env	*old_pwd;
	char	*cd;
	char	*current_path;

	pwd = data->env;
	old_pwd = data->env;
	cd = data->cmds->str[1];
	current_path = getcwd(NULL, 0);
	if (!pwd || !old_pwd || !current_path)
		return (1);		//	call the error function
	while (ft_strcmp_strict(pwd->key, "PWD") != 0)
		pwd = pwd->next;
	while (ft_strcmp_strict(old_pwd->key, "OLDPWD") != 0)
		old_pwd = old_pwd->next;
	if (chdir(cd) == -1)
	{
		ft_error_msg(pwd, old_pwd, cd, current_path);
		return (1);		//	call the error function
	}
	if (ft_add_value(pwd, old_pwd, current_path) != 0)
		return (1);		//	call the error function
	return (0);
}
