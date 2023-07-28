/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 23:41:01 by aabda             #+#    #+#             */
/*   Updated: 2023/07/28 00:50:36 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	i = 0;
	while (str1[i] && str2[i] && i < n - 1 && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
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
		kill_mini("Minishell");
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
		kill_mini("Minishell");
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
