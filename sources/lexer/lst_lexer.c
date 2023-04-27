/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:33:43 by gduchesn          #+#    #+#             */
/*   Updated: 2023/04/26 16:46:45 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*lst_new_arg(char *new_word, int token, int index)
{
	t_arg	*new;

	new = malloc(sizeof(t_arg));
	if (!new)
		exit(1);
	new->word = new_word;
	new->index = index;
	new->is_token = token;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

void	lst_add_arg(t_arg **arg, t_arg *new)
{
	t_arg	*snake;

	if (!new)
		return ;
	if (*arg)
	{
		snake = *arg;
		while (snake->next)
			snake = snake->next;
		snake->next = new;
	}
	else
		*arg = new;
}

void	lst_clear_arg(t_arg *arg)
{
	t_arg	*to_free;

	if (!arg)
		return ;
	while (arg)
	{
		to_free = arg;
		arg = arg->next;
		free(to_free->word);
		free(to_free);
	}
}

void	set_previous(t_arg *arg)
{
	t_arg	*tmp;
	t_arg	*head;

	head = arg;
	while (1)
	{
		tmp = arg;
		if (arg->next)
		{
			arg = arg->next;
			arg->previous = tmp;
		}
		else
			break ;
	}
}
