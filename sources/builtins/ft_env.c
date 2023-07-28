/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:39:36 by aabda             #+#    #+#             */
/*   Updated: 2023/07/28 07:53:16 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_var_env(t_data *data)
{
	t_env	*current;
	int		nbr_var_env;

	current = data->env;
	nbr_var_env = 0;
	while (current)
	{
		current = current->next;
		++nbr_var_env;
	}
	return (nbr_var_env);
}

static char	**ft_fill_array(t_data *data, char **tab, int size)
{
	t_env	*current;
	int		i;

	current = data->env;
	i = 0;
	while (i < size)
	{
		tab[i] = current->key;
		++i;
		current = current->next;
	}
	tab[i] = NULL;
	return (tab);
}

static void	ft_bubble_sort(char **tab, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (++i < size - 1)
	{
		j = -1;
		while (++j < size - i - 1)
		{
			if (ft_strncmp(tab[j], tab[j + 1], ft_strlen(tab[j])) > 0)
			{
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
		}
	}
}

static void	ft_env_sorted(t_data *data)
{
	t_env	*current;
	char	**env_sorted;
	int		nbr_var_env;
	int		i;

	nbr_var_env = ft_count_var_env(data);
	env_sorted = malloc(sizeof(char *) * (nbr_var_env + 1));
	if (!env_sorted)
		kill_mini("Minishell");
	env_sorted = ft_fill_array(data, env_sorted, nbr_var_env);
	ft_bubble_sort(env_sorted, nbr_var_env);
	i = 0;
	while (env_sorted[i])
	{
		current = data->env;
		while (ft_strcmp_strict(current->key, env_sorted[i]) != 0)
			current = current->next;
		if (ft_strcmp_strict(current->key, env_sorted[i]) == 0)
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		i++;
	}
	free(env_sorted);
	env_sorted = NULL;
}

int	ft_env(t_data *data)
{
	t_env	*current;
	int		argc;

	current = data->env;
	if (!current)
		return (1);
	argc = 0;
	while (data->cmds->tab[argc])
		++argc;
	if (argc == 1 && ft_strcmp_strict(data->cmds->tab[0], "export") == 0)
		ft_env_sorted(data);
	else
	{
		while (current)
		{
			printf("%s=%s\n", current->key, current->value);
			current = current->next;
		}
	}
	return (0);
}
