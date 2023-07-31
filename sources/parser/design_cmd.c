/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:31:02 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/31 16:48:16 by aabda            ###   ########.fr       */
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
		tab[i] = ft_strdup(pre_cmd->word);
		++i;
		pre_cmd = pre_cmd->next;
	}
	return (tab);
}

static void	ft_parse_word(t_data *data, t_arg *pre_cmd)
{
	t_dollar	*dollar;

	dollar = malloc(sizeof(t_dollar));
	if (!dollar)
		kill_mini("Minishell");
	dollar->str = pre_cmd->word;
	dollar->str = ft_dollar_handling(data, dollar, pre_cmd);
	free(dollar->i_dollar);
	free(dollar);
	fix_word(&pre_cmd->word);
}

void	check_empty_str(t_arg **head_cmd)
{
	t_arg	*snake;
	t_arg	*previous;

	snake = *head_cmd;
	previous = NULL;
	while (snake)
	{
		if (snake->word[0] == '\0')
		{
			if (!previous)
				*head_cmd = snake->next;
			else
				previous->next = snake->next;
			free(snake->word);
			ft_free((void **)&snake);
			snake = previous;
		}
		previous = snake;
		snake = snake->next;
	}
}

void	design_cmd(t_arg *pre_cmd,
	t_simple_cmds *new, t_data *data, t_arg *redirections)
{
	t_arg	*head_cmd;

	head_cmd = pre_cmd;
	while (pre_cmd)
	{
		ft_tilde_expander(new, pre_cmd);
		if (!pre_cmd->word)
			return ;
		ft_parse_word(data, pre_cmd);
		pre_cmd = pre_cmd->next;
	}
	check_empty_str(&head_cmd);
	new->tab = convert_to_tab(head_cmd);
	while (redirections)
	{
		ft_parse_word(data, redirections);
		redirections = redirections->next;
	}
}
