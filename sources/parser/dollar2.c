/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:30:21 by aabda             #+#    #+#             */
/*   Updated: 2023/06/23 15:06:06 by aabda            ###   ########.fr       */
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

static void	ft_create_words(char *str, char **words, int *i_dollar)
{
	int	i;
	int	j;
	int	k;
	int	word_len;

	i = -1;
	word_len = 0;
	while (i_dollar[++i] >= 0)
	{
		word_len = ft_count_char_to_end(str, i_dollar[i], '$', END_VAR_ENV);
		words[i] = malloc(sizeof(char) * (word_len + 1));
		if (!words[i])
			exit(EXIT_FAILURE);		//	call the error function
		j = i_dollar[i];
		k = 0;
		while (str && str[++j] && !ft_check_end_var(str[j]))
		{
			words[i][k] = str[j];
			++k;
		}
		words[i][k] = '\0';
	}
}

static char	**ft_catch_dollar_word(char *str, int *i_dollar)
{
	char	**words;
	int		i;

	i = 0;
	while (i_dollar[i] >= 0)
		++i;
	words = malloc(sizeof(char *) * ((i_dollar[i] * -1) + 1));
	if (!words)
		exit(EXIT_FAILURE);		//	call the error function
	words[i_dollar[i] * -1] = NULL;
	ft_create_words(str, words, i_dollar);
	return (words);
}

char	*ft_replace_dollar_by_env(t_data *data, char *str, int *i_dollar)
{
	char	**words;

	if (!i_dollar)
		return (str);
	words = ft_catch_dollar_word(str, i_dollar);
	str = ft_dollar_to_env(data, str, words, i_dollar);
	return (str);
}
