/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:36:46 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/28 11:30:39 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_splitndup(const char *s, int j, int i)
{
	char	*new;
	char	*str;

	str = (char *) s;
	str = str + i;
	i = 0;
	new = (char *)malloc(sizeof(char) * j + 1);
	if (!new)
		kill_mini("Minishell");
	while (i < j)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = 0;
	return (new);
}

static int	ft_string_loc(char const *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i])
			count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}

static int	ft_start_end(char const *s, int *i, int k, char c)
{
	while (s[k] && s[k] == c)
		k++;
	*i = k;
	while (s[k] && s[k] != c)
		k++;
	return (k);
}

static char	**freeland(char **tab, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(tab[i++]);
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	**finaltab;

	j = 0;
	k = 0;
	i = ft_string_loc(s, c);
	finaltab = (char **)malloc(sizeof(char *) * (i + 1));
	if (!finaltab)
		kill_mini("Minishell");
	finaltab[i] = NULL;
	l = i;
	while (j < l)
	{
		k = ft_start_end(s, &i, k, c);
		finaltab[j] = ft_splitndup(s, k - i, i);
		if (!finaltab[j])
			return (freeland(finaltab, j));
		j++;
	}
	free((void *)s);
	return (finaltab);
}
