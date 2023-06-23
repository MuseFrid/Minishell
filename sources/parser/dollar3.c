/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 21:58:19 by aabda             #+#    #+#             */
/*   Updated: 2023/06/23 14:31:22 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	ft_len_new_str(char *str, char *word, int word_i, int *i_dollar)
{
	int	len;

	len = ft_strlen(str);
	len -= ft_count_char_to_end(str, i_dollar[word_i], '$', END_VAR_ENV) + 1;
	len += ft_strlen(word);
	return (len);
}

static int	ft_fill_word(char *word, char *new_str, int j)
{
	int	i;

	i = -1;
	while (word[++i])
	{
		new_str[j] = word[i];
		++j;
	}
	return (j);
}

static char	*ft_process_str(char *str, char *word, int word_i, int *i_dollar)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = malloc(sizeof(char) * \
		ft_len_new_str(str, word, word_i, i_dollar) + 1);
	if (!new_str)
		exit(EXIT_FAILURE);		//	call error function
	i = -1;
	j = 0;
	while (++i < i_dollar[word_i])
	{
		new_str[j] = str[i];
		++j;
	}
	j = ft_fill_word(word, new_str, j);
	i += ft_count_char_to_end(str, i_dollar[word_i], '$', END_VAR_ENV);
	while (str && str[++i])
	{
		new_str[j] = str[i];
		++j;
	}
	new_str[j] = '\0';
	ft_free((void **)&str);
	return (new_str);
}

static void	ft_free_all_dollar_process(char **words, int *i_dol, int j)
{
	while (--j >= 0)
		ft_free((void **)&words[j]);
	ft_free((void **)&words);
	ft_free((void **)&i_dol);
}

char	*ft_dollar_to_env(t_data *data, char *str, char **words, int *i_dollar)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	while (i_dollar[++i] >= 0)
		;
	i = (i_dollar[i] * -1) + 1;
	j = i;
	while (--i >= 0)
	{
		tmp = ft_get_value_env(data, words[i]);
		if (tmp)
		{
			ft_free((void **)&words[i]);
			words[i] = tmp;
			tmp = NULL;
			str = ft_process_str(str, words[i], i, i_dollar);
			words[i] = NULL;
		}
	}
	ft_free_all_dollar_process(words, i_dollar, j);
	return (str);
}
