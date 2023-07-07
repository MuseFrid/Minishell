/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 21:58:19 by aabda             #+#    #+#             */
/*   Updated: 2023/07/07 22:11:35 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_create_p0(t_dollar *dollar, char **process, int idx)
{
	int	i;

	process = malloc(sizeof(char *) * 2);
	if (!process)
		exit(EXIT_FAILURE);		//	call error function
	i = 0;
	while (i < dollar->i_dollar[idx])
		i++;
	if (i)
	{

		process[0] = malloc(sizeof(char) * i + 1);
		if (!process[0])
			exit(EXIT_FAILURE);		//	call error function
		i = -1;
		while (++i < dollar->i_dollar[idx])
			process[0][i] = dollar->str[i];
		process[0][i] = '\0';
		return (process);
	}
	process[0] = NULL;
	return (process);
}

static int	ft_init_len(t_dollar *dollar, char **process, int idx)
{
	if (process[0])
		return (ft_strlen(dollar->str) - ft_strlen(process[0]) - \
			ft_strlen(dollar->words[idx]) - 1);
	else
		return (ft_strlen(dollar->str) - ft_strlen(dollar->words[idx]) - 1);
}

static char	**ft_create_p1(t_dollar *dollar, char **process, int idx)
{
	int	len;
	int	i;
	int	j;

	len = ft_init_len(dollar, process, idx);
	if (process[0])
		i = ft_strlen(process[0]) + ft_strlen(dollar->words[idx]);
	else
		i = ft_strlen(dollar->words[idx]);
	if (len)
	{
		process[1] = malloc(sizeof(char) * len + 1);
		if (!process[1])
			exit(EXIT_FAILURE);		//	call error function
		j = 0;
		while (dollar->str[++i])
		{
			process[1][j] = dollar->str[i];
			++j;
		}
		process[1][j] = '\0';
		return (process);
	}
	process[1] = NULL;
	return (process);
}

static void	ft_process_str(t_dollar *dollar, char *word, int index)
{
	char	**process;

	process = NULL;
	process = ft_create_p0(dollar, process, index);
	process = ft_create_p1(dollar, process, index);
	ft_join_p_word(dollar, process, word);
	// printf("{\n\t[index nº%d]\n\ti_dollar = %d\n\tprocess[0] = %s\n\tprocess[1] = %s\n\t%s\n}\n", index, dollar->i_dollar[index], process[0], process[1], dollar->str);
	// printf("{\n\ti = %d\n\tstr = %s\n\tindex du dollar a traiter = %d\n\tmot a remplacer = %s\n\ttaille du mot = %lu\n\tbon mot = %s\n}\n", i, dollar->str, dollar->i_dollar[i], dollar->words[i], ft_strlen(dollar->words[i]), word);
	// printf("[%lu]\n", ft_strlen(dollar->str) - ft_strlen(dollar->words[i]) - 1 + ft_strlen(word));
}

char	*ft_dollar_to_env(t_data *data, t_dollar *dollar)
{
	char	*tmp;
	int		i;

	i = -1;
	while (dollar->i_dollar[++i] >= 0)
		;
	i = (dollar->i_dollar[i] * -1) + 1;
	while (--i >= 0)
	{
		tmp = ft_get_value_env(data, dollar->words[i]);
		if (tmp)
			ft_process_str(dollar, tmp, i);
	}
	ft_free((void **)&dollar->i_dollar);
	i = -1;
	while (dollar->words[++i])
		ft_free((void **)&dollar->words[i]);
	ft_free((void **)&dollar->words);
	return (dollar->str);
}
