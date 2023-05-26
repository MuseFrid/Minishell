/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:07:19 by gduchesn          #+#    #+#             */
/*   Updated: 2023/05/26 15:30:58 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void	free_all(t_data *data)
{
	free_env(data->env);
	lst_clear_cmds(data->cmds);
	free(data);
	exit(ret_val);
}
