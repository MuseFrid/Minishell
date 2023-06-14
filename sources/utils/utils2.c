/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:23:37 by aabda             #+#    #+#             */
/*   Updated: 2023/06/14 16:49:00 by gduchesn         ###   ########.fr       */
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

int    ft_strcmp_strict(const char *s1, const char *s2)
{
    int    len_s1;
    int    len_s2;

    len_s1 = ft_strlen(s1);
    len_s2 = ft_strlen(s2);
    if (len_s1 == len_s2 && ft_strncmp(s1, s2, len_s1) == 0)
        return (0);
    return (1);
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

static int	ft_count_len(long *len, int *sign)
{
	long	count;
	long	i;

	count = 0;
	if (*len < 0)
	{
		*len = -(*len);
		count++;
		*sign = -1;
	}
	i = *len;
	while (i != 0)
	{
		i = i / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	count;
	long	len;
	int		sign;

	len = n;
	count = ft_count_len(&len, &sign);
	if (len == 0)
		return (ft_strdup("0"));
	str = (char *)malloc(sizeof(char) * (count + 1));
	if (!str)
		return (NULL);
	if (sign < 0)
		str[0] = 45;
	str[count] = 0;
	while (len != 0)
	{
		str[count - 1] = ((len % 10) + 48);
		len = len / 10;
		count--;
	}
	return (str);
}
