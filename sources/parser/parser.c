/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:24:15 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/28 00:14:56 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	its_token(t_arg **arg, t_simple_cmds **cmds)
{
	t_arg	*tmp;

	tmp = NULL;
	if (!(*arg && (*arg)->next))
		return (write(2, "Error\nno arguments after token |\n", 33));
	if ((*arg)->next->is_token)
		return (write(2, "Error\nunexpected token\n", 23));
	tmp = (*arg)->next->next;
	(*arg)->word = ft_strdup((*arg)->next->word);
	lst_unlink_arg((*arg));
	lst_add_arg(&(*cmds)->redirections, (*arg));
	(*arg) = tmp;
	return (0);
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
		{
			tmp = (*arg)->next;
			(*arg)->next = NULL;
			lst_clear_arg(*arg);
			*arg = tmp;
			return (pre_cmd);
		}
		if ((*arg)->is_token)
		{
			if (its_token(arg, &new))
			{
				*bool_quit = 1;
				if (new->redirections)
					lst_clear_arg(new->redirections);
				free(new);
				lst_clear_arg(*arg);
				return (lst_clear_arg(pre_cmd));
			}
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
	int				bool_quit;

	bool_quit = 0;
	pre_cmd = NULL;
	cmds = NULL;
	while (arg)
	{
		new = NULL;
		pre_cmd = NULL;
		lst_new_cmds(&new);
		pre_cmd = grab_redirections(&arg, new, &bool_quit);
		if (bool_quit)
		{
			lst_clear_cmds(cmds);
			return (NULL);
		}
		design_cmd(pre_cmd, new, data, new->redirections);
		lst_add_back_cmds(&cmds, new);
		lst_clear_arg(pre_cmd);
	}
	(*data).cmds = cmds;
	return (cmds);
}
