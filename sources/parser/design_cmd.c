/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:31:02 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/26 12:46:18 by aabda            ###   ########.fr       */
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
	printf("[design_cmd] dollar->str = %s%s%s\n", BOLDBLUE, pre_cmd->word, RESET);
	// len = ft_len_without_quote(dollar->str);
	// ft_str_without_quote(dollar, len);
	// exit(EXIT_FAILURE);
}

void	design_cmd(t_arg *pre_cmd, t_simple_cmds *new, t_data *data)
{
	while (pre_cmd)
	{
		ft_parse_word(data, pre_cmd);
		pre_cmd = pre_cmd->next;
	}
	// exit(EXIT_SUCCESS);
	(void) data;
	(void) new;
	(void) pre_cmd;
}
