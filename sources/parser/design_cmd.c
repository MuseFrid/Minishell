/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:31:02 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/26 23:19:27 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	ft_quote_len_str(char *str, int len, char c)
// {
// 	char	c2;
// 	int		i;

// 	if (c == '\'')
// 		c2 = '"';
// 	else
// 		c2 = '\'';
// 	i = -1;
// 	while (str && str[++i])
// 	{
// 		if ((str[i + 1] && str[i] == c) || (str[i + 1] && str[i] == c2))
// 		{
// 			if (str[i] == c)
// 				while (str[++i] != c)
// 					;
// 			else
// 				while (str[++i] != c2)
// 					;
// 			len -= 2;
// 		}
// 	}
// 	return (len);
// }

// static int	ft_len_without_quote(char *str)
// {
// 	int	len;
// 	int	i;

// 	len = ft_strlen(str);
// 	i = -1;
// 	while (str && str[++i])
// 	{
// 		if (str[i] == '\'' || str[i] == '"')
// 		{
// 			len = ft_quote_len_str(str, len, str[i]);
// 			break ;
// 		}
// 	}
// 	return (len);
// }
char **convert_to_tab(t_arg *pre_cmd)
{
	int	size;
	char	**tab;
	int	i;

	i = 0;
	size = lst_size_arg(pre_cmd);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		exit(1);
	tab[size] = NULL;
	while (pre_cmd)
	{
		tab[i] = ft_strdup(pre_cmd->word);
		if (!tab[i])
			exit(1);
		++i;
		pre_cmd = pre_cmd->next;
	}
	return (tab);
}

static void	ft_parse_word(t_data *data, t_arg *pre_cmd)
{
	t_dollar	*dollar;
	// int			len;

	dollar = malloc(sizeof(t_dollar));
	if (!dollar)
		exit(EXIT_FAILURE);		//	call the error function
	dollar->str = pre_cmd->word;
	dollar->str = ft_dollar_handling(data, dollar, pre_cmd);
	fix_word(&pre_cmd->word);
	// len = ft_len_without_quote(dollar->str);
	// ft_str_without_quote(dollar, len);
	// exit(EXIT_FAILURE);
}

static void	check_empty_str(t_arg **head_cmd)
{
	t_arg	*snake;
	t_arg	*previous;

	snake = *head_cmd;
	previous = NULL;
	while (snake)
	{
		if (snake->word[0] ==  '\0')
		{
			if (!previous)
				*head_cmd = snake->next;
			else
				previous->next = snake->next;
			free(snake->word);
			ft_free((void **)&snake);
			snake = previous;
		}
		previous = snake;
		snake = snake->next;
	}
}

void	design_cmd(t_arg *pre_cmd, t_simple_cmds *new, t_data *data, t_arg *redirections)
{
	t_arg	*head_cmd;

	head_cmd = pre_cmd;
	while (pre_cmd)
	{
		ft_parse_word(data, pre_cmd);
		pre_cmd = pre_cmd->next;
	}
	check_empty_str(&head_cmd);
	new->tab = convert_to_tab(head_cmd);
    while (redirections)
    {
        ft_parse_word(data, redirections);
        redirections = redirections->next;
    }
}
