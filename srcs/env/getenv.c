/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 12:51:54 by aabda             #+#    #+#             */
/*   Updated: 2023/04/19 01:16:57 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_add_value(t_data *data, t_env *new, char **envp, int i)
{
	t_env	*current;

	current = data->env;
	new->index = i;
	new->value = envp[i];
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
			exit(EXIT_FAILURE);
		ft_add_value(data, new, envp, i);
	}
}

void	ft_init_struct(t_data *data, char **envp)
{
	data->env = NULL;
	ft_getenv(data, envp);
}

/*
ft_ensure :
Check if current exist, if current doesn't exist = exit
loop on current to find if the ft_strncmp find the variable to ensure
	if the variable is the first one on the list :
		change the head of the list on the next one,
		put the prev on NULL and free current.

	if the variable is not the first element of the list :
		the variable next of the previous element = next element
		if a next element exist,
		the prev variable of the next element = previous
		and free current.
*/

void	ft_ensure(t_data *data, char *value)
{
	t_env	*current;

	current = data->env;
	if (!current)
		exit(EXIT_FAILURE);
	while (current)
	{
		if (ft_strncmp(value, current->value, ft_strlen(value)) == 0)
		{
			if (current == data->env)
			{
				data->env = current->next;
				current->next->prev = NULL;
			}
			else
			{
				current->prev->next = current->next;
				if (current->next)
					current->next->prev = current->prev;
			}
			free(current);
			break ;
		}
		current = current->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_env	*env;

	ft_init_struct(&data, envp);
	env = data.env;
	while (env)
	{
		printf("[%p] <- [%p] -> [%p] | %s\n", env->prev, env, env->next, env->value);
		env = env->next;
	}
	printf("\n========================\n\n");
	char *str = "COLORTERM";
	ft_ensure(&data, str);
	env = data.env;
	while (env)
	{
		printf("%s\n", env->value);
		env = env->next;
	}
	return (0);
}
