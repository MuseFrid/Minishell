/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:10:25 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/28 12:13:29 by gduchesn         ###   ########.fr       */
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
