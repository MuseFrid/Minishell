/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 12:51:54 by aabda             #+#    #+#             */
/*   Updated: 2023/05/04 03:01:50 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_fill_key_value(t_env *new, char **envp, int i)
{
	int	j;
	int	k;
	int	check_equal;

	j = 0;
	k = 0;
	check_equal = 0;
	while (envp[i][j])
	{
		if (!check_equal && envp[i][j - 1] == '=')
			check_equal = j;
		if (!check_equal)
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
		if (!equal_index && envp[i][j - 1] == '=')
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
	ft_fill_key_value(new, envp, i);
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

	i = -1;
	while (envp && envp[++i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			exit(EXIT_FAILURE);		//	need to put the error function !
		ft_add_value(data, new, envp, i);
	}
}
