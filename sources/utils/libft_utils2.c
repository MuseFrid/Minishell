/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 23:45:16 by aabda             #+#    #+#             */
/*   Updated: 2023/07/10 13:13:23 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!new)
		return (NULL);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = 0;
	return (new);
}

char	*ft_strndup(const char *str, int n)
{
	char	*new;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	if (len > n)
		len = n;
	new = (char *)malloc(sizeof(char) * len + 1);
	if (!new)
		return (NULL);
	while (str[i] && i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[len] = 0;
	return (new);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	if (!s)
		return (NULL);
	new = (char *) s;
	i = ft_strlen(new);
	if ((size_t) start > i)
		return (ft_strdup(""));
	if (i < len)
		return (ft_strdup((char *) s + start));
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	if (start >= i)
		return (new);
	i = 0;
	while (i < len)
		new[i++] = s[start++];
	new[i] = 0;
	return (new);
}

int	ft_atoi(const char *str)
{
	size_t		i;
	int			sign;
	long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
		if (result * sign < INT_MIN)
			return (0);
		if (result * sign > INT_MAX)
			return (-1);
	}
	return (result * sign);
}
