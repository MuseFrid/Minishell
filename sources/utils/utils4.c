/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 00:55:52 by aabda             #+#    #+#             */
/*   Updated: 2023/08/01 05:36:12 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_get_env_node_by_key(t_data *data, char *key)
{
	t_env	*node;

	node = data->env;
	while (node)
	{
		if (ft_strcmp_strict(node->key, key) == 0)
			break ;
		node = node->next;
	}
	return (node);
}
static void	ft_design_pwd_env(char **env, char *cd, int pick)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!(*env))
		return ;
	if (pick == 1)
	{
		ft_free((void **)&(*env));
		*env = ft_strdup(cd);
	}
	else
	{
		while (pick != 3 && (*env)[i])
			++i;
		printf("*env:%s value i: %d\n", *env, i);
		if (i > 0 && ((*env)[i - 1] != '/'))
			ft_design_pwd_env(env, "/", 3);
		tmp = ft_strjoin(*env, cd);
		ft_free((void **)&(*env));
		*env = tmp;
	}
}

int	ft_dir_not_found(t_data *data, char *cd)
{
	t_env	*tmp;

	if (chdir(cd) == -1)
	{
		ft_error_msg_cd(cd);
		return (1);
	}
	perror("cd: error retrieving current directory: \
getcwd: cannot access parent directories");
	ft_design_pwd_env(&data->hidden_env->oldpwd, data->hidden_env->pwd, 1);
	ft_design_pwd_env(&data->hidden_env->pwd, cd, 2);
	tmp = ft_get_env_node_by_key(data, "PWD");
	tmp->value = data->hidden_env->pwd;
	tmp = ft_get_env_node_by_key(data, "OLDPWD");
	tmp->value = data->hidden_env->oldpwd;
	return (0);
}
