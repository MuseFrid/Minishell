/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:24:15 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/31 18:05:42 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	its_token(t_arg **arg, t_simple_cmds **cmds)
{
	t_arg	*tmp;
	t_arg	*to_destroy;

	tmp = NULL;
	if (!(*arg && (*arg)->next))
		return (write(2, "Error\nno arguments after token |\n", 33));
	if ((*arg)->next->is_token)
		return (write(2, "Error\nunexpected token\n", 23));
	tmp = (*arg)->next->next;
	(*arg)->word = ft_strdup((*arg)->next->word);
	to_destroy = (*arg)->next;
	lst_unlink_arg(to_destroy);
	lst_clear_arg(to_destroy);
	lst_unlink_arg((*arg));
	lst_add_arg(&(*cmds)->redirections, (*arg));
	(*arg) = tmp;
	return (0);
}

static t_arg	*its_token_faild(int *bool_quit,
	t_simple_cmds *new, t_arg **arg, t_arg *pre_cmd)
{
	*bool_quit = 1;
	if (new->redirections)
		lst_clear_arg(new->redirections);
	free(new);
	lst_clear_arg(*arg);
	return (lst_clear_arg(pre_cmd));
}

t_arg	*arg_is_pipe(t_arg **arg, t_arg *tmp, t_arg *pre_cmd)
{
	tmp = (*arg)->next;
	(*arg)->next = NULL;
	lst_clear_arg(*arg);
	*arg = tmp;
	return (pre_cmd);
}

t_arg	*grab_redirections(t_arg **arg, t_simple_cmds *new, int *bool_quit)
{
	t_arg	*tmp;
	t_arg	*pre_cmd;

	tmp = NULL;
	pre_cmd = NULL;
	while (*arg)
	{
		if ((*arg)->is_token == PIPE)
			return (arg_is_pipe(arg, tmp, pre_cmd));
		if ((*arg)->is_token)
		{
			if (its_token(arg, &new))
				return (its_token_faild(bool_quit, new, arg, pre_cmd));
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

t_simple_cmds	*parser(t_arg *arg,
	t_data *data, t_simple_cmds *cmds, t_arg *pre_cmd)
{
	t_simple_cmds	*new;
	int				bool_quit;

	bool_quit = 0;
	while (arg)
	{
		new = NULL;
		pre_cmd = NULL;
		lst_new_cmds(&new);
		pre_cmd = grab_redirections(&arg, new, &bool_quit);
		if (bool_quit)
			return (lst_clear_cmds(cmds));
		design_cmd(&pre_cmd, new, data, new->redirections);
		if (new->end == 1)
		{
			lst_clear_arg(pre_cmd);
			return (lst_clear_cmds(cmds));
		}
		lst_add_back_cmds(&cmds, new);
		lst_clear_arg(pre_cmd);
	}
	(*data).cmds = cmds;
	return (cmds);
}
