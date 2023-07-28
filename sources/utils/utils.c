/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:41:32 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/28 02:47:13 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_fill_shlvl_no_env(t_env **current, t_env **b_last)
{
	*current = malloc(sizeof(t_env));
	if (!(*current))
		kill_mini("ft_fill_shlvl");
	(*current)->index = (*b_last)->index + 1;
	(*current)->key = ft_strdup("SHLVL");
	(*current)->value = ft_strdup("1");
	(*current)->next = NULL;
	(*current)->prev = *b_last;
	(*b_last)->next = *current;
}

static void	ft_fill_shlvl(t_env *current, t_env *b_last)
{
	int	val;

	if (!current)
		ft_fill_shlvl_no_env(&current, &b_last);
	else
	{
		val = ft_atoi(current->value);
		ft_free((void **)&current->value);
		if (val == INT_MAX)
			current->value = ft_strdup("0");
		else
			current->value = ft_itoa(val + 1);
	}
}

static void	ft_init_shlvl(t_data *data)
{
	t_env	*current;
	t_env	*b_last;

	current = data->env;
	while (current)
	{
		if (ft_strcmp_strict(current->key, "SHLVL") == 0)
		{
			ft_fill_shlvl(current, NULL);
			break ;
		}
		if (current && !current->next)
			b_last = current;
		current = current->next;
	}
	if (!current)
		ft_fill_shlvl(current, b_last);
}

static void	ft_init_heredoc(t_data *data)
{
	t_heredoc	*heredoc;

	heredoc = malloc(sizeof(t_heredoc));
	if (!heredoc)
		kill_mini("heredoc_init");
	heredoc->nbr_l = 0;
	heredoc->open_file = NULL;
	data->heredoc = heredoc;
}

void	ft_init_struct(t_data *data, char **envp)
{
	data->err_return_val = 0;
	data->env = NULL;
	ft_getenv(data, envp);
	ft_init_heredoc(data);
	ft_init_shlvl(data);
}
