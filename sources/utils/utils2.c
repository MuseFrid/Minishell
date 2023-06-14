/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:23:37 by aabda             #+#    #+#             */
/*   Updated: 2023/05/31 20:37:54 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmp_str_strict(const char *s1, const char *s2)
{
	int	len_s1;
	int	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (len_s1 == len_s2 && ft_strncmp(s1, s2, len_s1) == 0)
		return (0);
	return (1);
}

void	ft_free(void **value)
{
	free(*value);
	*value = NULL;
}

char	*ft_strldup(const char *str, int len)
{
	char	*new;
	int		i;
	int		size_str;

	i = 0;
	if (!str)
		return (NULL);
	size_str = ft_strlen(str);
	if (size_str > len)
		size_str = len;
	new = (char *)malloc(sizeof(char) * (size_str + 1));
	if (!new)
		exit(1);
	while (i < len && str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = 0;
	return (new);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strfinal;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	strfinal = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!strfinal)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		strfinal[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		strfinal[i++] = s2[j++];
	strfinal[i] = 0;
	return (strfinal);
}
