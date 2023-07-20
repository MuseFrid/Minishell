/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:23:13 by aabda             #+#    #+#             */
/*   Updated: 2023/07/13 12:01:01 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	quote[0] = simple quote
	quote[1] = double quote
*/

static void	ft_check_gate(int quote[2], int *check)
{
	if (quote[0] && !quote[1])
		*check = 0;
	else if (!quote[0] && !quote[1])
		*check = 1;
	else if (!quote[0] && quote[1] == 1)
		*check = 2;
	else if (*check && quote[0] == 1)
		*check = 2;
	else
		*check = 0;
}

static void	ft_check_quote(char c, int quote[2], int *check)
{
	if (quote[0] == 2)
		quote[0] = 0;
	if (quote[1] == 2)
		quote[1] = 0;
	if (c == '\'')
		++quote[0];
	if (c == '"')
		++quote[1];
	ft_check_gate(quote, check);
}


static int	ft_count_nbr_index(t_dollar *dollar)
{
	int	i;
	int	count;
	int	check;

	i = -1;
	count = 0;
	dollar->quote[0] = 0;
	dollar->quote[1] = 0;
	check = 0;
	while (dollar->str && dollar->str[++i])
	{
		ft_check_quote(dollar->str[i], dollar->quote, &check);
		if (check && dollar->str[i] == '$')
			++count;
	}
	dollar->is_quote = malloc(sizeof(char) * (count + 1));
	if (!dollar->is_quote)
		exit(EXIT_FAILURE);
	ft_memset(dollar->is_quote, '0', count);
	dollar->is_quote[count] = '\0';
	dollar->quote[0] = 0;
	dollar->quote[1] = 0;
	return (count);
}

static int	*ft_catch_dollar_index(t_dollar *dollar)
{
	int	i[2];
	int	count;
	int	check;

	count = ft_count_nbr_index(dollar);
	if (count)
	{
		dollar->i_dollar = malloc(sizeof(int) * (count + 1));
		if (!dollar->i_dollar)
			exit(EXIT_FAILURE);		//	call error function
		dollar->i_dollar[count] = count * -1;
		i[0] = -1;
		i[1] = 0;
		while (dollar->str && dollar->str[++i[0]])
		{
			ft_check_quote(dollar->str[i[0]], dollar->quote, &check);
			if (check && dollar->str[i[0]] == '$')
			{
				dollar->i_dollar[i[1]] = i[0];
				if (check == 2)
					dollar->is_quote[i[1]] = '1';
				printf("%c", dollar->is_quote[i[1]]);
				++i[1];
			}
		}
		printf("\n");
		return (dollar->i_dollar);
	}
	return (NULL);
}

char	*ft_dollar_handling(t_data *data, t_dollar *dollar, t_arg *pre_cmd)
{
	dollar->quote[0] = 0;
	dollar->quote[1] = 0;
	dollar->i_dollar = NULL;
	dollar->i_dollar = ft_catch_dollar_index(dollar);
	dollar->str = ft_replace_dollar_by_env(data, dollar, pre_cmd);
	return (dollar->str);
}
