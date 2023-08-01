/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 23:50:15 by aabda             #+#    #+#             */
/*   Updated: 2023/08/01 05:36:03 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_init_count_char_to_end(int *i, int index)
{
	if (!index)
		i[0] = 0;
	else
		i[0] = index;
	return (*i - 1);
}

static int	ft_check_hardcode(char *str, int index, int *check)
{
	*check = 0;
	if (str[index] == '$')
	{
		if (str[index + 1] == '?')
			*check = -42;
		if (!str[index + 1] || str[index + 1] == ' ' || str[index + 1] == '"')
			*check = -43;
	}
	return (*check);
}

int	ft_count_char_to_end(char *str, int index, char start, char *end)
{
	int	i[2];
	int	len;
	int	check;

	i[0] = ft_init_count_char_to_end(i, index);
	len = -1;
	if (ft_check_hardcode(str, index, &check) < 0)
		return (check);
	while (str && str[++i[0]])
	{
		if (str[i[0]] == start && !check)
		{
			++check;
			++i[0];
			++len;
		}
		i[1] = -1;
		while (check && end && end[++i[1]])
			if (str[i[0]] == end[i[1]])
				return (len);
		if (check)
			++len;
	}
	return (len);
}

void	ft_error_msg_cd(char *c_path)
{
	write(2, "Minishell: cd: ", 15);
	perror(c_path);
}
