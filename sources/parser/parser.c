/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:24:15 by gduchesn          #+#    #+#             */
/*   Updated: 2023/05/30 17:01:43 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	its_token(t_arg **arg, t_simple_cmds **cmds)
{
	t_arg	*tmp;

	tmp = NULL;
	if (!(*arg && (*arg)->next))
		return (printf("%sno arguments but care about |%s\n", RED, RESET));//no arguments but care about |
	if ((*arg)->next->is_token)
		return (printf("%sunexpected token%s\n", RED, RESET));
	tmp = (*arg)->next->next;
	(*arg)->word = ft_strdup((*arg)->next->word);//index to change
	//destroy_one_nod((*arg)->next);//no more need because content already dup
	lst_unlink_arg((*arg));
	lst_add_arg(&(*cmds)->redirections, (*arg));
	(*arg) = tmp;
	//destroy_nod(arg, 2, i);
	//cmds->redirections = arg;
	return (0);
}

t_arg	*grab_redirections(t_arg **arg, t_simple_cmds *new)
{
	t_arg	*tmp;
	t_arg	*pre_cmd;
	
	tmp = NULL;
	pre_cmd = NULL;
	while (*arg)
	{
		if ((*arg)->is_token == PIPE)
		{
			*arg = (*arg)->next;
			return (pre_cmd);
		}
		if ((*arg)->is_token)
		{
			if (its_token(arg, &new))
				exit(1); // free everything error fonction
		}
		else
		{
			lst_add_arg(&pre_cmd, *arg);
			tmp = *arg;
			*arg = (*arg)->next;
			tmp->next = NULL;
		}
	}
	return (pre_cmd);
}

void	print_parser(t_simple_cmds *cmds)
{
	t_simple_cmds	*tmp;
	tmp = cmds;
	while (tmp)
	{
		while (tmp->test_red)
		{
			printf("pre_cmd : %s\n", tmp->test_red->word);
			tmp->test_red = tmp->test_red->next;
		}
		while (tmp->redirections)
		{
			printf("redirections : %s token : %d\n", tmp->redirections->word, tmp->redirections->is_token);
			tmp->redirections = tmp->redirections->next;
		}
		tmp = tmp->next;
	}
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

//to remove
char **double_tab_to_keep_going(t_arg *pre_cmd)
{
	int	size;
	char	**tab;
	int	i;

	i = 0;
	size = lst_size_arg(pre_cmd);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	tab[size] = NULL;
	while (pre_cmd)
	{
		tab[i++] = ft_strdup(pre_cmd->word);
		pre_cmd = pre_cmd->next;
	}
	return (tab);
}

void	print_tab(t_simple_cmds *cmds)
{
	int	i;

	while (cmds)
	{
		i = 0;
		while (cmds->tab && cmds->tab[i])
			printf("%s\n", cmds->tab[i++]);
		cmds = cmds->next;
	}
}

t_simple_cmds	*parser(t_arg *arg, t_data *data)
{
	t_simple_cmds	*cmds;
	t_simple_cmds	*new;
	t_arg			*pre_cmd;

	pre_cmd = NULL;
	cmds = NULL;
	while (arg)
	{
		new = NULL;
		pre_cmd = NULL;
		lst_new_cmds(&new);
		pre_cmd = grab_redirections(&arg, new);
		new->test_red = pre_cmd;
		new->tab = double_tab_to_keep_going(pre_cmd);
		design_cmd(pre_cmd, new, data);
		lst_add_back_cmds(&cmds, new);
	}
	(*data).cmds = cmds;
	return (cmds);
}
