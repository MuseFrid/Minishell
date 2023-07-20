/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 21:58:19 by aabda             #+#    #+#             */
/*   Updated: 2023/07/18 02:44:34 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	**ft_create_p0(t_dollar *dollar, char **process, int idx)
// {
// 	int	i;

// 	process = malloc(sizeof(char *) * 2);
// 	if (!process)
// 		exit(EXIT_FAILURE);		//	call error function
// 	i = 0;
// 	while (i < dollar->i_dollar[idx])
// 		i++;
// 	if (i)
// 	{

// 		process[0] = malloc(sizeof(char) * i + 1);
// 		if (!process[0])
// 			exit(EXIT_FAILURE);		//	call error function
// 		i = -1;
// 		while (++i < dollar->i_dollar[idx])
// 			process[0][i] = dollar->str[i];
// 		process[0][i] = '\0';
// 		return (process);
// 	}
// 	process[0] = NULL;
// 	return (process);
// }

// static int	ft_init_len(t_dollar *dollar, char **process, int idx)
// {
// 	if (process[0])
// 		return (ft_strlen(dollar->str) - ft_strlen(process[0]) - \
// 			ft_strlen(dollar->words[idx]) - 1);
// 	else
// 		return (ft_strlen(dollar->str) - ft_strlen(dollar->words[idx]) - 1);
// }

// static char	**ft_create_p1(t_dollar *dollar, char **process, int idx)
// {
// 	int	len;
// 	int	i;
// 	int	j;

// 	len = ft_init_len(dollar, process, idx);
// 	if (process[0])
// 		i = ft_strlen(process[0]) + ft_strlen(dollar->words[idx]);
// 	else
// 		i = ft_strlen(dollar->words[idx]);
// 	if (len)
// 	{
// 		process[1] = malloc(sizeof(char) * len + 1);
// 		if (!process[1])
// 			exit(EXIT_FAILURE);		//	call error function
// 		j = 0;
// 		while (dollar->str[++i])
// 		{
// 			process[1][j] = dollar->str[i];
// 			++j;
// 		}
// 		process[1][j] = '\0';
// 		return (process);
// 	}
// 	process[1] = NULL;
// 	return (process);
// }

static int	ft_nbr_of_words(char *str)
{
	int	len;
	int	check;
	int	i;

	len = 0;
	check = 0;
	i = -1;
	while (str && str[++i])
	{
		while (str[i] == ' ')
		{
			check = 0;
			++i;
		}
		if (!check && ft_isalnum(str[i]))
		{
			++check;
			++len;
		}
	}
	return (len);
}

static char	*ft_fill_word(char *str, int len_word, int index)
{
	char	*word;
	int		i;
	int		j;

	word = malloc(sizeof(char) * (len_word + 1));
	if (!word)
		exit(EXIT_FAILURE);
	i = index - len_word -1;
	j = 0;
	while (str && str[++i] && str[i] != ' ')
	{
		word[j] = str[i];
		++j;
	}
	word[j] = '\0';
	return (word);
}

static void	ft_malloc_words(char *str, char **words, int total_malloc)
{
	int	len_word;
	int	i_malloc;
	int	i;

	i_malloc = -1;
	i = -1;
	while (++i_malloc < total_malloc)
	{
		len_word = 0;
		while (str && str[++i])
		{
			while (str[i] == ' ')
				++i;
			while (ft_isalnum(str[i]))
			{
				++len_word;
				++i;
			}
			break ;
		}
		words[i_malloc] = ft_fill_word(str, len_word, i);
	}
}

static char	**ft_get_words(char *str)
{
	char	**words;
	int		len;

	len = ft_nbr_of_words(str);
	words = malloc(sizeof(char *) * (len + 1));
	if (!words)
		exit(EXIT_FAILURE);		//	call error function
	words[len] = NULL;
	ft_malloc_words(str, words, len);
	return (words);
}

// static char	*ft_catch_end(t_dollar *dollar, t_arg *pre_cmd, char **words, int index)
// {
// 	(void)dollar;
// 	(void)words;
// 	(void)index;
// 	char	*end = NULL;
// 	int		i;

// 	i = dollar->i_dollar[index + 1];
// 	return (end);
// }

static void	ft_first_node(t_dollar *dollar, t_arg *pre_cmd, char *str, int index)
{
	char	*word;
	int		i;
	int		j;

	i = -1;
	word = malloc(sizeof(char) * (dollar->i_dollar[index] + ft_strlen(str) + 1));
	if (!word)
		exit(EXIT_FAILURE);
	i = -1;
	j = 0;
	while (++i < dollar->i_dollar[index] + (int)ft_strlen(str))
	{
		if (i < dollar->i_dollar[index])
			word[i] = pre_cmd->word[i];
		else
		{
			word[i] = str[j];
			++j;
		}
	}
	word[i] = '\0';
	dollar->str = ft_strdup(dollar->str);
	// printf("%s\n", dollar->str);
	ft_free((void **)&pre_cmd->word);
	pre_cmd->word = word;
}

static void	ft_last_node(t_dollar *dollar, t_arg *pre_cmd, char **words, int index)
{
	t_arg	*last;
	int		last_i;
	int		len;
	int		i;
	char	*str;

	last = pre_cmd;
	last_i = 0;
	while (words[last_i + 1])
		++last_i;
	++last_i;
	while (--last_i)
		last = last->next;
	len = (ft_strlen(dollar->str) + ft_strlen(last->word)) - (dollar->i_dollar[index] + ft_strlen(dollar->words[index]) + 1);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		exit(EXIT_FAILURE);		// call error function
	
	i = -1;
	last_i = dollar->i_dollar[index] + ft_strlen(dollar->words[index]) + 1;
	printf("%d\n", len);
	while (++i < len)
	{
		if (i < (int)ft_strlen(last->word))
		{
			str[i] = last->word[i];
			// printf("%s%c%s", BOLDMAGENTA, last->word[i], RESET);
		}
		else
		{
			str[i] = dollar->str[last_i];
			++last_i;
		}
		printf("%s%c%s", BOLDCYAN, str[i], RESET);
	}
	printf("\n");
	str[i] = '\0';
	ft_free((void **)&last->word);
	last->word = str;
	// printf("%sdollar->str = %s\ndollar->words[index] = %s\nlast->word = %s\ndollar->i_dollar[index] = %d\nlen = %d\nstr = %s%s\n", BOLDGREEN, dollar->str, dollar->words[index], last->word, dollar->i_dollar[index], len, str, RESET);








	// (void)index;
	// t_arg	*last;
	// int		i;
	// int		j;
	// int		len;
	// char	*str;

	// last = pre_cmd;
	// j = 0;
	// len = ft_strlen(dollar->str) - (ft_strlen(dollar->words[index]) + 1) + ft_strlen(words[j]);
	// while (words[j + 1])
	// 	++j;
	// i = -1;
	// while (++i < j)
	// 	last = last->next;
	// str = malloc(sizeof(char) * len + 1);
	// if (!str)
	// 	exit(EXIT_FAILURE);		//	call error function
	// i = -1;
	// int	k = j;
	// j = dollar->i_dollar[index] + ft_strlen(dollar->words[index]) + 1;
	// printf("j = %d\ndollar->str = %s\nwords[j] = %s\n", j, dollar->str, words[k]);
	// // while (++i < len)
	// // {
	// // 	if (i < (int)ft_strlen(last->word))
	// // 		str[i] = last->word[i];
	// // 	else
	// // 	{
	// // 		str[i] = dollar->str[j];
	// // 		++j;
	// // 	}
	// // 	printf("%s%c%s", BOLDCYAN, str[i], RESET);
	// // }
	// str[i] = '\0';
	// printf("str = %s\n", str);
}

static void	ft_create_nodes_words(t_dollar *dollar, t_arg *pre_cmd, char **words, int index)
{
	t_arg	*new;
	t_arg	*tmp;
	t_arg	*last;
	int		i;

	new = NULL;
	tmp = NULL;
	last = pre_cmd->next;
	ft_first_node(dollar, pre_cmd, words[0], index);
	i = 0;
	while (words && words[++i] && words[i])
	{
		if (new)
			tmp = new;
		new = lst_new_arg(words[i], 0);
		if (i == 1)
			pre_cmd->next = new;
		else
			tmp->next = new;
		if (!words[i + 1])
			ft_last_node(dollar, pre_cmd, words, index);
	}
	new->next = last;
}

static void	ft_expand_and_join2(t_arg *pre_cmd, char *str, int *i, int j)
{
	while (pre_cmd->word[j])
	{
		str[*i] = pre_cmd->word[j];
		++(*i);
		++j;
	}
}

static void	ft_expand_and_join(t_dollar *dollar, t_arg *pre_cmd, char *env_val, int	index)
{
	char	*str;
	int		len;
	int		i;
	int		j;
	
	len = ft_strlen(pre_cmd->word) - (ft_strlen(dollar->words[index]) + 1) + ft_strlen(env_val);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		exit(EXIT_FAILURE);		// call error function
	i = -1;
	while (pre_cmd->word && pre_cmd->word[++i] && i < dollar->i_dollar[index])
		str[i] = pre_cmd->word[i];
	j = -1;
	while (env_val[++j])
	{
		str[i] = env_val[j];
		++i;
	}
	j = dollar->i_dollar[index] + ft_strlen(dollar->words[index]) + 1;
	ft_expand_and_join2(pre_cmd, str, &i, j);
	str[i] = '\0';
	dollar->str = ft_strdup(str);
	ft_free((void **)&pre_cmd->word);
	pre_cmd->word = str;

}

static void	ft_process_str(t_dollar *dollar, t_arg *pre_cmd, char *word, int index)
{
	// (void)pre_cmd;
	int		i;
	// char	**process;
	char	**words;

	i = -1;
	// process = NULL;
	words = NULL;
	printf("pre_cmd->word = [%s]\n", pre_cmd->word);
	// printf("%sword = [%s]%s\n", BOLDGREEN, word, RESET);
	// printf("dollar->words[index] = [%s]\n", dollar->words[index]);
	while (dollar->is_quote[index] == '0' && word[++i])
	{
		if (word[i] == ' ' && word[i + 1])
			words = ft_get_words(word);
	}
	if (words)
		ft_create_nodes_words(dollar, pre_cmd, words, index);
	else
		ft_expand_and_join(dollar, pre_cmd, word, index);
	// ft_fill_start(dollar, pre_cmd, word, index);


		while (words && pre_cmd)
		{
			printf("current = [%p]\tword = [%s]\t next = [%p]\n", pre_cmd, pre_cmd->word, pre_cmd->next);
			pre_cmd = pre_cmd->next;
		}
	// while (pre_cmd)
	// {
	// 	printf("current = [%p]\tword = [%s]\t next = [%p]\n", pre_cmd, pre_cmd->word, pre_cmd->next);
	// 	pre_cmd = pre_cmd->next;
	// }
	// printf("ICI\n");
	// exit(EXIT_FAILURE);
		// for (int i = 0; words[i]; i++)
		// 	printf("\n===%s[%s]%s===\n", MAGENTA, words[i], RESET);

	
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
	ft_free((void **)&dollar->i_dollar);
	i = -1;
	while (dollar->words[++i])
		ft_free((void **)&dollar->words[i]);
	ft_free((void **)&dollar->words);
	return (dollar->str);
}
