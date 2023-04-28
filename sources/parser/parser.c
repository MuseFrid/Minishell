/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:16:20 by gduchesn          #+#    #+#             */
/*   Updated: 2023/04/27 19:39:33 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_one_nod(t_arg *arg)
{
	t_arg	*before;
	t_arg	*after;

	before = NULL;
	after = NULL;
	if (arg->previous)
	{
		before = arg->previous;
		before->next = after;
	}
	if (arg->next)
	{
		after = arg->next;
		after->previous = before;
	}
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

int	its_token(t_arg *arg, t_simple_cmds *cmds, int *i)
{
	t_arg			*tmp;

	tmp = NULL;
	if (arg && arg->next)
	{
		tmp = arg->next->next;
		if (arg->next->is_token)
		{
			printf("%sunexpected token%s\n", RED, RESET);
			return (1);
		}
		arg->word = ft_strdup(arg->next->word);//index to change
		destroy_one_nod(arg->next);
		lst_unlink_arg(arg);
		lst_add_arg(&cmds->test_red, arg);
		arg = tmp;
		(*i) -= 2;
		//destroy_nod(arg, 2, i);
		//cmds->redirections = arg;
	}
	else
	{
		printf("%sno arguments but care about |%s\n", RED, RESET);
		return (1);//no arguments but care about |
	}
	return (0);
}

t_simple_cmds	*new_cmds(t_arg *head, int i)
{
	t_simple_cmds	*new;
	t_arg			*arg;

	arg = head;
	new = lst_new_cmds(arg, i);
	if (!new)
		exit (1);
	while (arg && arg->is_token != PIPE)
	{
		if (arg->is_token)
		{
			printf("les token\n");
			if (its_token(arg, new, &i))
				return (NULL);
		}
		if (arg)
			arg = arg->next;
		if (arg)
			printf("%s\n", arg->word);
	}
	return (new);
}

void	printing_parsing(t_simple_cmds *head)
{
	t_simple_cmds *test;
	t_arg	*look;
	t_arg	*ui;
	test = head;
	write(1, BLUE, ft_strlen(BLUE));
	printf("parsing :\n");
	write(1, RESET, ft_strlen(RESET));
	while (test)
	{
		printf("New cmd \\/\n");
		look = test->redirections;
		while (look && look->is_token != 1)
		{
			printf("word : \"%s\" token : \"%d\"\n", look->word, look->is_token);
			look = look->next;
		}		
		ui = test->test_red;
		while (ui && ui->is_token != 1)
		{
			printf("%sword : \"%s\" token : \"%d\"%s\n", RED, ui->word, ui->is_token, RESET);
			ui = ui->next;
		}
		printf("\n");
		test = test->next;
	}
	write(1, BLUE, ft_strlen(BLUE));
	printf("end parsing\n\n");
	write(1, RESET, ft_strlen(RESET));
}

void	parser(t_arg *arg, t_data data)
{
	t_simple_cmds	*head;
	t_arg			*arg_head;
	t_arg			*snake;
	int				i;
	
	(void) data;
	i = 0;
	arg_head = arg;
	snake = arg;
	head = NULL;
	while (snake)
	{
		i++;
		if (snake->is_token == PIPE || snake->next == NULL)
		{
		//	lst_add_back_cmds(&head, lst_new_cmds(arg, i));
			lst_add_back_cmds(&head, new_cmds(arg, i));
			if (snake->next)
				arg = snake->next;
			i = 0;
		}
		snake = snake->next;
	}
	printing_parsing(head);//test
	lst_clear_cmds(head);
	lst_clear_arg(arg_head);
}
