/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:23:16 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/31 20:23:05 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*lst_clear_cmds(t_simple_cmds **head)
{
	t_simple_cmds	*tmp;
	int				i;

	i = 0;
	while (*head)
	{
		if ((*head)->tab)
		{
			while ((*head)->tab[i])
				free((*head)->tab[i++]);
			free((*head)->tab);
		}
		lst_clear_arg(&((*head)->redirections));
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
		i = 0;
	}
	*head = NULL;
	return (NULL);
}

void	lst_add_back_cmds(t_simple_cmds **head, t_simple_cmds *new)
{
	t_simple_cmds	*snake;

	if (!new)
		return ;
	snake = *head;
	if (snake)
	{
		while (snake->next)
			snake = snake->next;
		new->prev = snake;
		snake->next = new;
	}
	else
		*head = new;
}

void	lst_new_cmds(t_simple_cmds **new)
{
	*new = malloc(sizeof(t_simple_cmds));
	if (!new)
		kill_mini("Minishell");
	(*new)->tab = NULL;
	(*new)->builtin = NULL;
	(*new)->pid = -2;
	(*new)->end = 0;
	(*new)->redirections = NULL;
	(*new)->next = NULL;
	(*new)->prev = NULL;
}

int	lst_size_arg(t_arg *pre_cmd)
{
	int	i;

	i = 0;
	if (pre_cmd)
	{
		while (pre_cmd && ++i)
			pre_cmd = pre_cmd->next;
	}
	return (i);
}
