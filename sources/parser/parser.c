/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:16:20 by gduchesn          #+#    #+#             */
/*   Updated: 2023/05/03 20:59:07 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printing_parsing(t_simple_cmds *head);

int	its_token(t_arg **arg, t_simple_cmds **cmds)
{
	if (!(*arg && (*arg)->next))
		return (printf("%sno arguments but care about |%s\n", RED, RESET));//no arguments but care about |
	if ((*arg)->next->is_token)
		return (printf("%sunexpected token%s\n", RED, RESET));
	(*arg)->word = ft_strdup((*arg)->next->word);//index to change
	destroy_one_nod((*arg)->next);//no more need because content already dup
	lst_unlink_arg((*arg));
	lst_add_arg(&(*cmds)->redirections, (*arg));
	(*arg) = (*arg)->next->next;
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
	while (arg && arg->is_token != PIPE)
	{
		if (arg->is_token)
		{
			if (its_token(&arg, new))
				return (NULL);
		}
		else
		{
			tmp = arg;
			arg = arg->next;
			lst_add_arg(&before_tab, tmp);
			tmp->next = NULL;
		}
	}
	return (before_tab);
}

t_simple_cmds	*new_cmd(t_arg *head, t_simple_cmds *cmds)
{
	t_simple_cmds	*new;
	t_arg			*pre_tab;

	pre_tab = NULL;
	new = NULL;
	lst_new_cmds(&new);
	if (!new)
		exit (1);
	pre_tab = fill_cmd(head, &new);
	if (pre_tab == NULL)
		return (NULL);
	new->redirection = pre_tab;
	lst_add_back_cmds(&cmds, new);
	create_tab(head, &new);
	new = NULL;
	if (!new)// need to free everything
		return (NULL);
	return (cmds);
}

void	parser(t_arg *arg, t_data data)
{
	t_simple_cmds	*head;
	t_arg			*arg_head;
	
	arg_head = arg;
	head = NULL;
	new_cmd(arg, head);// after that cmds are finished so we got str[][] and redirection in every nod
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
