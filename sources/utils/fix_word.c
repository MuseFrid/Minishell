/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:14:22 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/28 00:23:07 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redesign_word(char **word, int *i, char type, int *bool_quotes)
{
	char	*tmp;
	char	*redesign;
	char	*tmp2;
	int		j;

	if (*bool_quotes == 0)
		*bool_quotes = 1;
	tmp = ft_strndup((*word), *i);
	j = *i + 1;
	while ((*word)[j] && (*word)[j] != type)
		j++;
	redesign = ft_strndup(((*word) + *i + 1), (j - *i - 1));
	tmp2 = ft_strjoin(tmp, redesign);
	free(tmp);
	free(redesign);
	*i = ft_strlen(tmp2);
	tmp = ft_strjoin(tmp2, ((*word) + j + 1));
	free(tmp2);
	ft_free((void **)&(*word));
	*word = tmp;
}

int	fix_word(char **word)
{
	int	bool_quotes;
	int	i;

	i = 0;
	bool_quotes = 0;
	while ((*word) && (*word)[i])
	{
		if ((*word)[i] == '\'')
			redesign_word(word, &i, '\'', &bool_quotes);
		else if ((*word)[i] == '\"')
			redesign_word(word, &i, '\"', &bool_quotes);
		else
			++i;
	}
	return (bool_quotes);
}
