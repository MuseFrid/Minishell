/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:31:02 by gduchesn          #+#    #+#             */
/*   Updated: 2023/08/01 12:36:26 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_to_tab(t_arg *pre_cmd)
{
	int		size;
	char	**tab;
	int		i;

	i = 0;
	size = lst_size_arg(pre_cmd);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		kill_mini("Minishell");
	tab[size] = NULL;
	while (pre_cmd)
	{
		if (pre_cmd->word[0])
		{
			tab[i] = ft_strdup(pre_cmd->word);
			++i;
		}
		pre_cmd = pre_cmd->next;
	}
	return (tab);
}

static void	ft_parse_word(t_data *data, t_arg *pre_cmd)
{
	t_dollar	*dollar;

	if (!(pre_cmd->is_token == 5))
	{
		dollar = malloc(sizeof(t_dollar));
		if (!dollar)
			kill_mini("Minishell");
		dollar->str = pre_cmd->word;
		dollar->str = ft_dollar_handling(data, dollar, pre_cmd);
		free(dollar->i_dollar);
		free(dollar);
	}
	fix_word(&pre_cmd->word);
}

void	design_cmd(t_arg **pre_cmd,
	t_simple_cmds *new, t_data *data, t_arg *redirections)
{
	t_arg	*head_cmd;

	head_cmd = *pre_cmd;
	while (*pre_cmd)
	{
		ft_tilde_expander(new, *pre_cmd);
		if (!(*pre_cmd)->word)
			return ;
		ft_parse_word(data, *pre_cmd);
		*pre_cmd = (*pre_cmd)->next;
	}
	new->tab = convert_to_tab(head_cmd);
	while (redirections)
	{
		ft_parse_word(data, redirections);
		redirections = redirections->next;
	}
	*pre_cmd = head_cmd;
}
