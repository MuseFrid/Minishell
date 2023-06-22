/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:31:02 by gduchesn          #+#    #+#             */
/*   Updated: 2023/06/21 23:04:31 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	dans la gestion des quotes, il faut :
		quand je suis dans des simple quote :
			écrire tout se qu'il y a dans les simples quote en brut
		quand je suis dans des doubles quote :
			écrire tout se qu'il y a dans les doubles quotes 
			et si il y a des varibales d'environement remplacer par la bonne valeur
*/

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

static int	ft_trigger_quote(char *str)
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

static void	ft_parse_word(t_data *data, char *str)
{
	(void)data;
	int	len;

	len = ft_trigger_quote(str);
	len = ft_check_dollar(data, str, len);

}

void	design_cmd(t_arg *pre_cmd, t_simple_cmds *new, t_data *data)
{
	while (pre_cmd)
	{
		printf("%s", GREEN);
		printf("%s\n", pre_cmd->word);
		printf("%s", RESET);
		ft_parse_word(data, pre_cmd->word);
		pre_cmd = pre_cmd->next;
	}
	(void) data;
	(void) new;
	(void) pre_cmd;
}
