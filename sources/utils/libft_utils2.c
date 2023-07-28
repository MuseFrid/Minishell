/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 23:45:16 by aabda             #+#    #+#             */
/*   Updated: 2023/07/28 07:27:54 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *str)
{
	char	*new;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	new = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!new)
		kill_mini("Minishell");
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
		kill_mini("Minishell");
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
		kill_mini("Minishell");
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
	long long int	i;
	long long int	num;
	long long int	save;
	int				sign;

	i = 0;
	sign = 1;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
		if (str[i++] == 45)
			sign *= -1;
	while (str[i] && ft_isdigit(str[i]))
	{
		save = num;
		num = (num * 10) + (str[i++] - 48);
		if ((sign == -1 && (-num) > 2147483648 && --errno)
			|| (sign == 1 && save > num && --errno))
			return (-1);
	}
	if (sign == -1)
		return (-num);
	return (num);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)b;
	while (i < len)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
