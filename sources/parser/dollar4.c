/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:12:56 by aabda             #+#    #+#             */
/*   Updated: 2023/07/07 22:09:23 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_fill_p0(char **process, char *str, int *j)
{
	int	i;

	i = -1;
	while (process[0] && process[0][++i])
	{
		str[*j] = process[0][i];
		++(*j);
	}
}

static void	ft_fill_p1(char **process, char *str, int *j)
{
	int	i;

	i = -1;
	while (process[1] && process[1][++i])
	{
		str[*j] = process[1][i];
		++(*j);
	}
}

void	ft_join_p_word(t_dollar *dollar, char **process, char *word)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(process[0]) + ft_strlen(word) + ft_strlen(process[1]);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		exit(EXIT_FAILURE);		//	call error function
	j = 0;
	ft_fill_p0(process, str, &j);
	i = -1;
	while (word[++i])
	{
		str[j] = word[i];
		++j;
	}
	i = -1;
	ft_fill_p1(process, str, &j);
	str[j] = '\0';
	ft_free((void **)&dollar->str);
	dollar->str = str;
}
