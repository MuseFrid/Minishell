/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:31:02 by gduchesn          #+#    #+#             */
/*   Updated: 2023/06/28 10:52:20 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_quote_len_str(char *str, int len, char c)
{
	char	c2;
	int		i;

	if (c == '\'')
		c2 = '"';
	else
		c2 = '\'';
	i = -1;
	while (str && str[++i])
	{
		if ((str[i + 1] && str[i] == c) || (str[i + 1] && str[i] == c2))
		{
			if (str[i] == c)
				while (str[++i] != c)
					;
			else
				while (str[++i] != c2)
					;
			len -= 2;
		}
	}
	return (len);
}

static int	ft_len_without_quote(char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			len = ft_quote_len_str(str, len, str[i]);
			break ;
		}
	}
	return (len);
}

// static void	ft_str_without_quote(char *str, int len)
// {
// 	char	*new_str;

// 	new_str = malloc(sizeof(char) * len + 1);
// 	if (!new_str)
// 		exit(EXIT_FAILURE);
	
// }

static void	ft_parse_word(t_data *data, char *str)
{
	int	len;

	len = 0;
	str = ft_dollar_handling(data, str);
	len = ft_len_without_quote(str);
	// ft_str_without_quote(str, len);
	printf("[%d]%s\n", len, str);
}

void	design_cmd(t_arg *pre_cmd, t_simple_cmds *new, t_data *data)
{
	while (pre_cmd)
	{
		ft_parse_word(data, pre_cmd->word);
		pre_cmd = pre_cmd->next;
	}
	(void) data;
	(void) new;
	(void) pre_cmd;
}
