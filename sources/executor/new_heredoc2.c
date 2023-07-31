/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_heredoc2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:04:19 by aabda             #+#    #+#             */
/*   Updated: 2023/07/31 18:05:26 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmp_delimiter(char c)
{
	static char	delimiter[] = END_VAR_ENV;
	int			i;

	i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*find_env_variable(char *str, int i, int j, t_data data)
{
	while (data.env)
	{
		if ((j - i - 1) == (int)ft_strlen(data.env->key)
			&& !ft_strncmp((str + i + 1), data.env->key, (j - i - 1)))
			return (ft_strdup(data.env->value));
		data.env = data.env->next;
	}
	return (ft_strdup(""));
}

char	*heredoc_join(char *str, char *env_value, int i, int j)
{
	char	*tmp;
	char	*start;

	tmp = ft_strndup(str, i);
	start = ft_strjoin(tmp, env_value);
	free(tmp);
	free(env_value);
	tmp = ft_strjoin(start, (str + j));
	free(start);
	free(str);
	return (tmp);
}
