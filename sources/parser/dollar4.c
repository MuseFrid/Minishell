/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:10:25 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/31 16:55:12 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_dollar_struct(t_dollar *dollar)
{
	int	i;

	i = -1;
	ft_free((void **)&dollar->i_dollar);
	while (dollar->words[++i])
		ft_free((void **)&dollar->words[i]);
	ft_free((void **)&dollar->words);
	return (dollar->str);
}

void	ft_start_str(t_dollar *dollar, char *str, int *i, int index)
{
	while (*i < dollar->i_dollar[index])
	{
		str[*i] = dollar->str[*i];
		++(*i);
	}
}

void	ft_word_str(char *str, char *word, int *i)
{
	int	j;

	j = -1;
	while (word && word[++j])
	{
		str[*i] = word[j];
		++(*i);
	}
}

char	*ft_escape_first_digit(t_dollar *dollar, int index)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * ft_strlen(dollar->words[index]));
	if (!str)
		kill_mini("Minishell");
	i = 0;
	while (dollar->words[index] && dollar->words[index][++i])
		str[i - 1] = dollar->words[index][i];
	str[i - 1] = '\0';
	return (str);
}

int	ft_size_i_dollar(t_dollar *dollar)
{
	int	i;

	i = -1;
	while (dollar->i_dollar[++i] >= 0)
		;
	return (dollar->i_dollar[i] * -1);
}
