/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_-i.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 04:38:55 by aabda             #+#    #+#             */
/*   Updated: 2023/05/28 18:40:15 by aabda            ###   ########.fr       */
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
		exit(EXIT_FAILURE);
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
	if (!current)
		exit(EXIT_FAILURE);
	while (current->next)
		current = current->next;
	new = malloc(sizeof(t_env));
	if (!new)
		exit(EXIT_FAILURE);
	new->index = 2;
	new->key = ft_strdup("SHLVL");
	new->value = ft_strdup("1");
	current->next = new;
	new->next = NULL;
	new->prev = current;
}

static void	ft_underscore_without_env(t_data *data)
{
	t_env	*current;
	t_env	*new;

	current = data->env;
	if (!current)
		exit(EXIT_FAILURE);
	while (current->next)
		current = current->next;
	new = malloc(sizeof(t_env));
	if (!new)
		exit(EXIT_FAILURE);
	new->index = 3;
	new->key = ft_strdup("_");
	new->value = ft_strdup("./minishell");		//	maybe false
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
