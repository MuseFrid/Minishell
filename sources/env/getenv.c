/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 12:51:54 by aabda             #+#    #+#             */
/*   Updated: 2023/05/08 13:44:52 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_fill_key_value(t_env *new, char **envp, int i, int equal_index)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (envp[i][j])
	{
		if (j < equal_index)
			new->key[j] = envp[i][j];
		else
		{
			new->value[k] = envp[i][j];
			k++;
		}
		j++;
	}
}

static void	ft_key_value(t_env *new, char **envp, int i)
{
	int	j;
	int	equal_index;

	j = 0;
	equal_index = 0;
	while (envp[i][j])
	{
		if (!equal_index && envp[i][j] == '=')
			equal_index = j;
		j++;
	}
	new->key = malloc(sizeof(char) * equal_index + 1);
	if (!new->key)
		exit(EXIT_FAILURE);		//	need to put the error function !
	new->key[equal_index] = '\0';
	new->value = malloc(sizeof(char) * (j - equal_index) + 1);
	if (!new->value)
		exit(EXIT_FAILURE);		//	need to put the error function !
	new->value[j - equal_index] = '\0';
	ft_fill_key_value(new, envp, i, equal_index);
}

static void	ft_add_value(t_data *data, t_env *new, char **envp, int i)
{
	t_env	*current;

	current = data->env;
	new->index = i;
	ft_key_value(new, envp, i);
	new->next = NULL;
	if (!current)
	{
		new->prev = NULL;
		data->env = new;
	}
	else
	{
		while (current->next)
		{
			if (current->next->prev != current)
				current->next->prev = current;
			current = current->next;
		}
		current->next = new;
		new->prev = current;
	}
}

void	ft_getenv(t_data *data, char **envp)
{
	t_env	*new;
	int		i;

	if (!envp || !envp[0])
		ft_run_without_env(data);
	i = -1;
	while (envp && envp[++i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			exit(EXIT_FAILURE);		//	need to put the error function !
		ft_add_value(data, new, envp, i);
	}
}
