/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:24:15 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/26 17:08:22 by gduchesn         ###   ########.fr       */
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
		design_cmd(pre_cmd, new, data, new->redirections);
		lst_add_back_cmds(&cmds, new);
		lst_clear_arg(pre_cmd);
	}
	(*data).cmds = cmds;
	return (cmds);
}
