/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 21:58:19 by aabda             #+#    #+#             */
/*   Updated: 2023/07/28 12:13:20 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_expand_str(t_dollar *dollar,
	t_arg *pre_cmd, char *word, int index)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	len = (ft_strlen(dollar->str) - (ft_strlen(dollar->words[index]) + 1)) \
		+ ft_strlen(word);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		kill_mini("Minishell");
	i = 0;
	ft_start_str(dollar, str, &i, index);
	ft_word_str(str, word, &i);
	j = dollar->i_dollar[index] + (int)ft_strlen(dollar->words[index]) + 1;
	while (i < len)
	{
		str[i] = dollar->str[j];
		++i;
		++j;
	}
	str[i] = '\0';
	ft_free((void **)&dollar->str);
	dollar->str = str;
	pre_cmd->word = dollar->str;
	free(word);
}

static void	ft_create_node(t_arg *pre_cmd, t_arg *last, char *word, int count)
{
	t_arg	*new;
	t_arg	*tmp;

	tmp = pre_cmd;
	while (tmp->next != last)
		tmp = tmp->next;
	if (count == 1)
		tmp->word = word;
	else
	{
		new = lst_new_arg(word, 0);
		tmp->next = new;
		new->next = last;
	}
}

static void	ft_create_word(t_dollar *dollar,
	t_arg *pre_cmd, t_arg *last, int len_word[2])
{
	char		*word;
	int			i;
	static int	count = 0;

	if (dollar->str == pre_cmd->word)
		count = 0;
	word = malloc(sizeof(char) * (len_word[1] - len_word[0] + 1));
	if (!word)
		kill_mini("Minishell");
	i = 0;
	while (len_word[0] < len_word[1])
	{
		word[i] = dollar->str[len_word[0]];
		++len_word[0];
		++i;
	}
	len_word[0] = -1;
	len_word[1] = 0;
	word[i] = '\0';
	++count;
	ft_create_node(pre_cmd, last, word, count);
}

static void	ft_parse_for_create_node(t_arg *pre_cmd, t_dollar *dollar, int i)
{
	t_arg	*last;
	int		len_word[2];

	last = pre_cmd->next;
	len_word[0] = -1;
	len_word[1] = 0;
	while (++i < (int)ft_strlen(dollar->str))
	{
		if (dollar->str[i] && dollar->str[i] == ' ')
			continue ;
		if (len_word[0] == -1 && dollar->str[i] != ' ')
			len_word[0] = i;
		while (len_word[0] != -1 && dollar->str[i] && dollar->str[i] != ' ')
		{
			if (dollar->str[i] == '"')
				while (dollar->str[++i] != '"')
					;
			++i;
			len_word[1] = i;
		}
		if (len_word[0] != -1 && len_word[1])
			ft_create_word(dollar, pre_cmd, last, len_word);
	}
}

char	*ft_dollar_to_env(t_data *data, t_dollar *dollar, t_arg *pre_cmd)
{
	char	*tmp;
	int		i;
	int		check;

	i = -1;
	check = 0;
	while (dollar->i_dollar[++i] >= 0)
		;
	i = (dollar->i_dollar[i] * -1);
	while (--i >= 0)
	{
		if (ft_strcmp_strict(dollar->words[i], "?") == 0)
		{
			tmp = ft_itoa(ret_val);
			check = 1;
		}
		else
			tmp = ft_strdup(ft_get_value_env(data, dollar->words[i]));
		ft_expand_str(dollar, pre_cmd, tmp, i);
		if (check && check--)
			ft_free((void **)&dollar->words[i]);
	}
	ft_parse_for_create_node(pre_cmd, dollar, -1);
	return (free_dollar_struct(dollar));
}
