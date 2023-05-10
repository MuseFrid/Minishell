/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_strjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:22:51 by gduchesn          #+#    #+#             */
/*   Updated: 2023/05/10 15:23:57 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*free_before_return(char const *s1, char const *s2, char *return_str)
{
	free((void *)s1);
	free((void *)s2);
	return (return_str);
}

char	*parsing_strjoin(char const *s1, char const *s2)
{
	char	*strfinal;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1)
		i = ft_strlen(s1);
	if (s2)
		j = ft_strlen(s2);
	strfinal = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!strfinal)
		return (free_before_return(s1, s2, strfinal));
	i = -1;
	while (s1[++i])
		strfinal[i] = s1[i];
	j = 0;
	while (s2[j])
		strfinal[i++] = s2[j++];
	strfinal[i] = 0;
	return (free_before_return(s1, s2, strfinal));
}
