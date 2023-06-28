/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:23:13 by aabda             #+#    #+#             */
/*   Updated: 2023/06/23 15:31:13 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	quote[0] = simple quote
	quote[1] = double quote
*/

static void	ft_check_quote(char c, int quote[2])
{
	if (quote[0] == 2)
		quote[0] = 0;
	if (quote[1] == 2)
		quote[1] = 0;
	if (c == '\'')
		++quote[0];
	if (c == '"')
		++quote[1];
}

static void	ft_check_gate(int quote[2], int *check)
{
	if (quote[0] && !quote[1])
		*check = 0;
	else if (!quote[0] && !quote[1])
		*check = 1;
	else if (!quote[0] && quote[1] == 1)
		*check = 1;
	else if (*check && quote[0] == 1)
		*check = 1;
	else
		*check = 0;
}

static int	ft_count_nbr_index(char *str)
{
	int	i;
	int	count;
	int	quote[2];
	int	check;

	i = -1;
	count = 0;
	quote[0] = 0;
	quote[1] = 0;
	check = 0;
	while (str && str[++i])
	{
		ft_check_quote(str[i], quote);
		ft_check_gate(quote, &check);
		if (check && str[i] == '$')
			++count;
	}
	return (count);
}

static int	*ft_catch_dollar_index(int *i_dollar, char *str)
{
	int	i[2];
	int	count;
	int	quote[2];
	int	check;

	count = ft_count_nbr_index(str);
	if (count)
	{
		i_dollar = malloc(sizeof(int) * (count + 1));
		if (!i_dollar)
			exit(EXIT_FAILURE);		//	call error function
		i_dollar[count] = count * -1;
		i[0] = -1;
		quote[0] = 0;
		quote[1] = 0;
		i[1] = 0;
		while (str && str[++i[0]])
		{
			ft_check_quote(str[i[0]], quote);
			ft_check_gate(quote, &check);
			if (check && str[i[0]] == '$')
			{
				i_dollar[i[1]] = i[0];
				++i[1];
			}
		}
		return (i_dollar);
	}
	return (NULL);
}

char	*ft_dollar_handling(t_data *data, char *str)
{
	int	quote[2];
	int	*i_dollar;

	quote[0] = 0;
	quote[1] = 0;
	i_dollar = NULL;
	i_dollar = ft_catch_dollar_index(i_dollar, str);
	str = ft_replace_dollar_by_env(data, str, i_dollar);
	return (str);
}
