/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:32:50 by gduchesn          #+#    #+#             */
/*   Updated: 2023/04/30 19:34:32 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote(char *str, int *i, int *j, char to_find)
{
	while (1)
	{
		(*i)++;
		(*j)++;
		if (!(str[*i] != to_find && str[*i]))
			break ;
	}
	if (!str[*i])
		return (ga_error(UNCLOSED_QUOTE));
	return (SUCCESS);
}

static void	touch_i(int *i, int pick)
{
	if (pick % 2 != 0 && pick != 1)
		(*i) += 2;
	else if (pick != 0)
		(*i)++;
}

int	is_token(char *str, int *i, int able_touch_i)
{
	int	pick;

	pick = 0;
	if (str[*i])
	{
		if (str[*i] == '|')
			pick = PIPE;
		if (str[*i] == '>')
		{
			if (str[(*i) + 1] && str[(*i) + 1] == '>')
				pick = D_GREATER;
			else
				pick = GREATER;
		}
		if (str[*i] == '<')
		{
			if (str[(*i) + 1] && str[(*i) + 1] == '<')
				pick = D_LOWER;
			else
				pick = LOWER;
		}
	}
	if (able_touch_i == 1)
		touch_i(i, pick);
	return (pick);
}

t_arg	*lexer(t_arg *arg, char *str)
{
	int		i;
	int		j;
	char	*new_word;
	t_arg	*new;

	i = 0;
	while (1)
	{
		j = 0;
		while (str[i] == ' ')
			i++;
		while (str[i] != ' ' && str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
				if (quote(str, &i, &j, str[i]))
					exit(1);
			if (is_token(str, &i, 0))
				break ;
			i++;
			j++;
		}
		if (j > 0)
		{
			new_word = ft_substr(str, i - j, j);
			new = lst_new_arg(new_word, NOT_A_TOKEN);
			lst_add_arg(&arg, new);
		}
		if (is_token(str, &i, 0))
		{
			new = lst_new_arg(NULL, is_token(str, &i, 1));
			lst_add_arg(&arg, new);
		}
		if (!str[i])
			break ;
	}
	//test
	new = arg;
	printf("%slexer part :%s\n", GREEN, RESET);
//	while (new->next)
//		new = new->next;
	while (new)
	{
		if (new->word)
			printf("%s\n", new->word);
		else
			printf("%d\n", new->is_token);
		new = new->next;
		//new = new->previous;
	}
	printf("%sEnd lexer part.%s\n\n", GREEN, RESET);
	//
	return (arg);
}
