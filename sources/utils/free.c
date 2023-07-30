/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:07:19 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/29 18:24:15 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(void **value)
{
	if (*value)
		free(*value);
	*value = NULL;
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		ft_free((void **)&env->key);
		ft_free((void **)&env->value);
		tmp = env;
		env = env->next;
		ft_free((void **)&tmp);
	}
}

void	free_all(t_data *data)
{
	free_env(data->env);
	lst_clear_cmds(data->cmds);
	exit(1);
}

void	free_before_new_cmds(t_data *data, char *str)
{
	lst_clear_cmds(data->cmds);
	unlink(HEREDOC_FILE);
	errno = 0;
	ft_free((void **)&str);
}
