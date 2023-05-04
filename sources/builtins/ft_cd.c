/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:31:37 by aabda             #+#    #+#             */
/*   Updated: 2023/05/04 16:16:25 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_add_value(t_env *pwd, t_env *old_pwd, char *current_path)
{
	if (ft_strncmp(old_pwd->key, "OLDPWD", 6) == 0)
	{
		free(old_pwd->value);
		old_pwd->value = current_path;
	}
	current_path = getcwd(NULL, 0);
	printf("%s\n", current_path);
	if (!current_path)
		return (1);		//	call the error function
	if (ft_strncmp(old_pwd->key, "PWD", 3) == 0)
	{
		free(pwd->value);
		pwd->value = current_path;
	}
	else
		return (1);		// call the error function
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
	// cd =				//	variable in struct where the user need to cd
	current_path = getcwd(NULL, 0);
	printf("%s\n", current_path);
	if (!pwd || !old_pwd || !current_path)
		return (1);		//	call the error function
	while (ft_strncmp(pwd->key, "PWD", 3) == 0)
		pwd = pwd->next;
	while (ft_strncmp(old_pwd->key, "OLDPWD", 6) == 0)
		old_pwd = old_pwd->next;
	if (chdir(cd) == -1)
		return (1);		//	call the error function
	if (ft_add_value(pwd, old_pwd, current_path) != 0)
		return (1);		//	call the error function
	return (0);
}
