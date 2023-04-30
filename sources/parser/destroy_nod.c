/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_nod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:44:49 by gduchesn          #+#    #+#             */
/*   Updated: 2023/04/30 14:59:09 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_one_nod(t_arg *arg)
{
	t_arg	*before;
	t_arg	*after;

	if (!arg)
		return ;
	before = arg->previous;
	after = arg->next;
	if (before)
		before->next = after;
	if (after)
		after->previous = before;
	arg->next = NULL;
	arg->previous = NULL;
	lst_clear_arg(arg);
	arg = NULL;
}

void	destroy_nod(t_arg *arg, int how_many, int *i)
{
	int		j;
	t_arg	*tmp;
	t_arg	*head;

	head = arg->previous;
	j = 0;
	printf("%d\n", how_many);
	while (j++ < how_many && arg)
	{
		if (arg->previous)
		{
			if (arg->next)
				arg->previous->next = arg->next;
			else
				arg->previous->next = NULL;
		}
		if (arg->next)
		{
			if (arg->previous)
				arg->next->previous = arg->previous;
			else
				arg->next->previous = NULL;
		}
		(*i)--;
		tmp = arg;
		arg = arg->next;
		tmp->next = NULL;
		lst_clear_arg(tmp);
		tmp = NULL;
	}
	t_arg *new = head;
	printf("%sentre\n", RED);
	while (new)
	{
		if (new->word)
			printf("%s\n", new->word);
		else
			printf("%d\n", new->is_token);
		new = new->next;
		//new = new->previous;
	}
		printf("%s", RESET);
	printf("%d\n", j);
	if (j != how_many + 1)
		printf("there is a issue in destroy_nod\n");
}
