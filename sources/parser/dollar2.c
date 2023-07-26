/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:30:21 by aabda             #+#    #+#             */
/*   Updated: 2023/07/26 13:40:26 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_end_var(char c)
{
	const char	*str;
	int			i;

	str = END_VAR_ENV;
	i = -1;
	while (str && str[++i])
	{
		if (str[i] == c)
			return (1);
	}
	return (0);
}

static void	ft_create_words(t_dollar *dollar)
{
	int	i;
	int	j;
	int	k;
	int	word_len;

	i = -1;
	word_len = 0;
	while (dollar->i_dollar[++i] >= 0)
	{
		word_len = ft_count_char_to_end(dollar->str, \
			dollar->i_dollar[i], '$', END_VAR_ENV);
		if (word_len == -42)
		{
			dollar->words[i] = ft_strdup("?");
			if (!dollar->words[i])
				exit(EXIT_FAILURE);
		}
		else
		{
			dollar->words[i] = malloc(sizeof(char) * (word_len + 1));
			if (!dollar->words[i])
				exit(EXIT_FAILURE);		//	call the error function
			j = dollar->i_dollar[i];
			k = 0;
			while (dollar->str && dollar->str[++j] \
				&& !ft_check_end_var(dollar->str[j]))
			{
				dollar->words[i][k] = dollar->str[j];
				++k;
			}
			dollar->words[i][k] = '\0';
		}
	}
}

static char	**ft_catch_dollar_word(t_dollar *dollar)
{
	int		i;

	i = 0;
	while (dollar->i_dollar[i] >= 0)
		++i;
	dollar->words = malloc(sizeof(char *) * ((dollar->i_dollar[i] * -1) + 1));
	if (!dollar->words)
		exit(EXIT_FAILURE);		//	call the error function
	dollar->words[dollar->i_dollar[i] * -1] = NULL;
	ft_create_words(dollar);
	return (dollar->words);
}

char	*ft_replace_dollar_by_env(t_data *data, t_dollar *dollar, t_arg *pre_cmd)
{
	if (!dollar->i_dollar)
		return (dollar->str);
	dollar->words = ft_catch_dollar_word(dollar);
	dollar->str = ft_dollar_to_env(data, dollar, pre_cmd);
	return (dollar->str);
}
