/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:32:50 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/28 11:57:39 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quote(char *str, int *i, int *j, char to_find)
{
	while (1)
	{
		(*i)++;
		(*j)++;
		if (!(str[*i] != to_find && str[*i]))
			break ;
	}
	if (!str[*i])
		return (write(2, UNCLOSED_QUOTE, ft_strlen(UNCLOSED_QUOTE)));
	return (0);
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

static int	begining_lexer(char *str, int *i, int *j, t_arg *arg)
{
	while (str[*i] == ' ')
		++(*i);
	while (str[*i] != ' ' && str[*i])
	{
		if (str[*i] == '\'' || str[*i] == '\"')
		{
			if (quote(str, i, j, str[*i]))
			{
				lst_clear_arg(arg);
				return (1);
			}
		}
		if (is_token(str, i, 0))
			break ;
		++(*i);
		++(*j);
	}
	return (0);
}

t_arg	*lexer(t_arg *arg, char *str, int i)
{
	int		j;
	char	*new_word;
	t_arg	*new;

	while (1)
	{
		j = 0;
		if (begining_lexer(str, &i, &j, arg))
			return (NULL);
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
	return (arg);
}
