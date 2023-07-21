/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 21:58:19 by aabda             #+#    #+#             */
/*   Updated: 2023/07/21 18:32:15 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_start_str(t_dollar *dollar, char *str, int *i, int index)
{
	while (*i < dollar->i_dollar[index])
	{
		str[*i] = dollar->str[*i];
		++(*i);
	}
}

static void	ft_word_str(char *str, char *word, int *i)
{
	int	j;

	j = -1;
	while (word && word[++j])
	{
		str[*i] = word[j];
		++(*i);
	}
}

static void	ft_expand_str(t_dollar *dollar, char *word, int index)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	len = (ft_strlen(dollar->str) - (ft_strlen(dollar->words[index]) + 1)) \
		+ ft_strlen(word);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		exit(EXIT_FAILURE);		//	call error function
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
}

static void	ft_process_str(t_dollar *dollar, t_arg *pre_cmd, char *word, int index)
{
	printf("=====================================\n");
	printf("[ft_process_str] = %s\ndollar->str = [%s]\ndollar->words[index] = %s\npre_cmd->word = [%s]\nword = [%s]%s\n", BOLDGREEN, dollar->str, dollar->words[index], pre_cmd->word, word, RESET);
	ft_expand_str(dollar, word, index);
	pre_cmd->word = dollar->str;
	printf("=====================================\n");
}

static void	ft_create_node(t_arg *pre_cmd, char *word, int count)
{
	t_arg	*new;
	t_arg	*tmp;
	t_arg	*tmp2;
	t_arg	*last;

	tmp = pre_cmd;
	tmp2 = pre_cmd;
	last = NULL;
	if (count != 1)
	{
		new = lst_new_arg(word, 0);
		last = tmp->next;
		tmp->next = new;
		new->next = last;
	}
	else
		tmp->word = word;
	printf("%d - %s\n", count, word);
	while (tmp2)
	{
		printf("%sCurrent = [%p]\t[%s]\tNext = [%p]%s\n", BOLDMAGENTA, tmp2, tmp2->word, tmp2->next, RESET);
		tmp2 = tmp2->next;
	}
}

static void	ft_catch_word(t_dollar *dollar, t_arg *pre_cmd, int start, int end)
{
	char		*word;
	int			i;
	static int	count = 0;

	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		exit(EXIT_FAILURE);		//	call error function
	i = 0;
	while (start < end)
	{
		word[i] = dollar->str[start];
		++start;
		++i;
	}
	word[i] = '\0';
	++count;
	ft_create_node(pre_cmd, word, count);
}

static void	ft_parse_for_create_node(t_arg *pre_cmd, t_dollar *dollar)
{
	int	start;
	int	end;
	int	i;

	start = -1;
	end = 0;
	i = -1;
	while (++i < (int)ft_strlen(dollar->str))
	{
		while (dollar->str[i] && dollar->str[i] == ' ')
			++i;
		if (start == -1 && dollar->str[i] != ' ')
			start = i;
		while (dollar->str[i] && dollar->str[i] != ' ')
		{
			++i;
			end = i;
		}
		if (start != -1 && end)
		{
			ft_catch_word(dollar, pre_cmd, start, end);
			start = -1;
			end = 0;
		}
	}
}

char	*ft_dollar_to_env(t_data *data, t_dollar *dollar, t_arg *pre_cmd)
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
			ft_process_str(dollar, pre_cmd, tmp, i);
	}
	ft_parse_for_create_node(pre_cmd, dollar);
	ft_free((void **)&dollar->i_dollar);
	i = -1;
	while (dollar->words[++i])
		ft_free((void **)&dollar->words[i]);
	ft_free((void **)&dollar->words);
	return (dollar->str);
}
