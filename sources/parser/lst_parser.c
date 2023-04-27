/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:23:16 by gduchesn          #+#    #+#             */
/*   Updated: 2023/04/27 16:59:29 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_clear_cmds(t_simple_cmds *head)
{
	t_simple_cmds	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
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
		snake->next = new;
	}
	else
		*head = new;
}

t_simple_cmds	*lst_new_cmds(t_arg *arg, int i)
{
	t_simple_cmds	*new;

	new = malloc(sizeof(t_simple_cmds));
	if (!new)
		exit(1);
	new->str = NULL;
	//builtin = NULL;
	new->num_redirections = i;
	new->hd_file_name = NULL;
	new->redirections = arg;
	new->test_red = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
