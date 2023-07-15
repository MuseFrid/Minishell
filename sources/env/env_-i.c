/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_-i.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 04:38:55 by aabda             #+#    #+#             */
/*   Updated: 2023/07/15 20:29:49 by gduchesn         ###   ########.fr       */
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
	if (!new->key)
		kill_mini("env_pwd");
	new->value = ft_strdup(path);
	if (!new->value)
		kill_mini("env_pwd");
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
	if (!new->key)
		kill_mini("env_shlvl");
	new->value = ft_strdup("0");
	if (!new->value)
		kill_mini("env_shlvl");
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
	if (!new->key)
		kill_mini("env_underscore");
	new->value = ft_strdup("./minishell");
	if (!new->value)
		kill_mini("env_underscore");
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
