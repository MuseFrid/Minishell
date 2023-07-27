/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_-i.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 04:38:55 by aabda             #+#    #+#             */
/*   Updated: 2023/07/28 00:11:57 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_env_pwd(t_data *data)
{
	t_env	*new;
	char	*path;

	new = malloc(sizeof(t_env));
	path = getcwd(NULL, 0);
	if (!new || !path)
		kill_mini("env_pwd");
	new->index = 1;
	new->key = ft_strdup("PWD");
	new->value = ft_strdup(path);
	new->next = NULL;
	new->prev = NULL;
	data->env = new;
}

static void	ft_env_shlvl(t_data *data)
{
	t_env	*current;
	t_env	*new;

	current = data->env;
	while (current->next)
		current = current->next;
	new = malloc(sizeof(t_env));
	if (!new)
		kill_mini("env_shlvl");
	new->index = 2;
	new->key = ft_strdup("SHLVL");
	new->value = ft_strdup("0");
	current->next = new;
	new->next = NULL;
	new->prev = current;
}

static void	ft_underscore_without_env(t_data *data)
{
	t_env	*current;
	t_env	*new;

	current = data->env;
	while (current->next)
		current = current->next;
	new = malloc(sizeof(t_env));
	if (!new)
		kill_mini("env_underscore");
	new->index = 3;
	new->key = ft_strdup("_");
	new->value = ft_strdup("./minishell");
	current->next = new;
	new->next = NULL;
	new->prev = current;
}

void	ft_run_without_env(t_data *data)
{
	ft_env_pwd(data);
	ft_env_shlvl(data);
	ft_underscore_without_env(data);
}
