/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:16:20 by gduchesn          #+#    #+#             */
/*   Updated: 2023/04/25 18:03:47 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	lst_add_back_cmds(t_simple_cmds **head, t_simple_cmds *new)
{
	if (!new)
		return ;
	if (*head)
	{
		while ((*head)->next)
			(*head) = (*head)->next;
		(*head)->next = new;
	}
	else
		*head = new;
}

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

void	parser(t_arg *arg, t_data data)
{
	t_simple_cmds	*head;
	t_arg			*arg_head;
	t_arg			*snake;
	int				i;
	
	i = 0;
	arg_head = arg;
	snake = arg;
	head = NULL;
	while (snake)
	{
		i++;
		if (snake->is_token == PIPE || snake->next == NULL)
		{
			lst_add_back_cmds(&head, lst_new_cmds(arg, i));
			if (snake->next)
				arg = snake->next;
			i = 0;
		}
		snake = snake->next;
	}
	//test
	t_simple_cmds *test;
	test = head;
	printf("parsing :\n");
	while (test)
	{
		if (test->redirections->word)
			printf("%s\n", test->redirections->word);
		else
			printf("%d\n", test->redirections->is_token);
		test = test->next;
	}
	printf("end parsing\n\n");
	//
	lst_clear_cmds(head);
	(void) data;
	lst_clear_arg(arg_head);
}
