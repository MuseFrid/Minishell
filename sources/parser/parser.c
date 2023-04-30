/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:16:20 by gduchesn          #+#    #+#             */
/*   Updated: 2023/04/30 21:55:10 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printing_parsing(t_simple_cmds *head);

int	its_token(t_arg *arg, t_simple_cmds **cmds)
{
	t_arg			*tmp;

	if (!(arg && arg->next))
		return (printf("%sno arguments but care about |%s\n", RED, RESET));//no arguments but care about |
	tmp = arg->next->next;
	if (arg->next->is_token)
		return (printf("%sunexpected token%s\n", RED, RESET));
	arg->word = ft_strdup(arg->next->word);//index to change
	destroy_one_nod(arg->next);//no more need because content already dup
	lst_unlink_arg(arg);
	lst_add_arg(&(*cmds)->redirections, arg);
	arg = tmp;
	//destroy_nod(arg, 2, i);
	//cmds->redirections = arg;
	return (0);
}

int	cmd_size(t_arg *arg)
{
	int	i;

	i = 0;
	while (arg && arg->is_token != PIPE)
	{
		arg = arg->next;
		i++;
	}
	return (i);
}

char	**init_tab(int size)
{
	char	**tab;
	int		i;

	i = 0;
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	while (i <= size)
		tab[i++] = NULL;
	return (tab);
}

void	create_tab(t_arg *arg, t_simple_cmds **cmd)
{
	int		i;
	t_arg	*tmp;

	i = 0;
	printf("%d\n", cmd_size(arg));
	(*cmd)->str = init_tab(cmd_size(arg));
	while (arg)
	{
		if (arg->is_token == PIPE)
		{
			destroy_one_nod(arg);
			break ;
		}
		(*cmd)->str[i++] = ft_strdup(arg->word);
		tmp = arg;
		arg = arg->next;
		lst_unlink_arg(tmp);
		lst_clear_arg(tmp);
	}
}

t_arg	*fill_cmd(t_arg *arg, t_simple_cmds **new)
{
	t_arg	*before_tab;
	t_arg	*tmp;
	
	before_tab = NULL;
	while (arg && arg->next && arg->is_token != PIPE)
	{
		if (arg->is_token)
		{
			if (its_token(arg, new))
				return (NULL);
		}
		tmp = arg;
		arg = arg->next;
		lst_add_arg(&before_tab, tmp);
		tmp->next = NULL;
	}
	return (before_tab);
}

t_simple_cmds	*new_cmd(t_arg *head, t_simple_cmds *cmds)
{
	t_simple_cmds	*new;
	t_arg			*cmd;

	cmd = NULL;
	lst_new_cmds(&new);
	if (!new)
		exit (1);
	while (1)
	{
		cmd = fill_cmd(head, &new);
		if (cmd == NULL)
			break ;
		lst_add_back_cmds(&cmds, new);
		create_tab(head, &new);
	}
	if (!new)// need to free everything
		return (NULL);
	return (cmds);
}

void	parser(t_arg *arg, t_data data)
{
	t_simple_cmds	*head;
	//t_arg			*snake;
	
	//
	t_arg			*arg_head;
	arg_head = arg;
	//
	head = NULL;
	//snake = arg;
	head = new_cmd(arg, head);
	/*while (snake)
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
	}*/
	printing_parsing(head);//test
	lst_clear_cmds(head);
	lst_clear_arg(arg_head);
	(void) data;
}

void	printing_parsing(t_simple_cmds *head)
{
	t_simple_cmds *test;
	t_arg	*ui;
	int		i;

	i = 0;
	test = head;
	write(1, BLUE, ft_strlen(BLUE));
	printf("parsing :\n");
	write(1, RESET, ft_strlen(RESET));
	while (test)
	{
		printf("New cmd \\/\n");
		while (test->str[i])
		{
			printf("word : \"%s\"hihi\n", test->str[i]);
			i++;
		}		
		ui = test->redirections;
		while (ui)
		{
			printf("%sword : \"%s\" token : \"%d\"%s\n", RED, ui->word, ui->is_token, RESET);
			ui = ui->next;
		}
		printf("\n");
		i = 0;
		test = test->next;
	}
	write(1, BLUE, ft_strlen(BLUE));
	printf("end parsing\n\n");
	write(1, RESET, ft_strlen(RESET));
}
