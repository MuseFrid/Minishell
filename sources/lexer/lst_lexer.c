/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:33:43 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/31 20:20:34 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*lst_new_arg(char *new_word, int token)
{
	t_arg	*new;

	new = malloc(sizeof(t_arg));
	if (!new)
		kill_mini("Minishell : lst_new_arg");
	new->word = new_word;
	new->is_token = token;
	new->next = NULL;
	return (new);
}

void	lst_unlink_arg(t_arg *arg)
{
	arg->next = NULL;
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

void	*lst_clear_arg(t_arg **arg)
{
	t_arg	*to_free;

	if (!(*arg))
		return (NULL);
	while (*arg)
	{
		to_free = *arg;
		*arg = (*arg)->next;
		lst_unlink_arg(to_free);
		free(to_free->word);
		free(to_free);
	}
	*arg = NULL;
	return (NULL);
}

/*void	set_previous(t_arg *arg)
{
	t_arg	*tmp;
	t_arg	*head;

	if (!arg)
		return ;
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
}*/
