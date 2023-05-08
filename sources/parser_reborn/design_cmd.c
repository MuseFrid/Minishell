/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:37:19 by gduchesn          #+#    #+#             */
/*   Updated: 2023/05/08 17:25:43 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_data(t_data data)
{
	while (data.env)
	{
		printf("%s\n", data.env->key);
		data.env = data.env->next;
	}
}

int	is_interaction(char c)
{
	static char	str[] = "\'\"$";
	int			i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	if (i == 3)
		return (0);
	return (i + 1);
}

void	handle_quotes(char *str, int tmp, int *i, int *start)
{
	char	stop;

	stop = str[(*i)++];
	*start = *i;
	while (str[*i] != stop)
	{
		if (tmp == DOUBLE_QUOTES && str[*i] == '$')
			;
	}
	(void) str;
	(void) tmp;
	return ;
}

void	looking_for_expend(char *str, t_data data)
{
	int	i;
	int	tmp;
	int	start;
	char	*final_str;

	i = 0;
	tmp = 0;
	(void) data;
	start = i;
	final_str = NULL;
	while (str[i])
	{
		tmp = is_interaction(str[i]);
		if (tmp && tmp != DOLLAR)
		{
			final_str = parsing_strjoin(final_str, ft_substr(str, start, i - start));
			handle_quotes(str, tmp, &i, &start);
		}
		//if (str[i] == '\'')
		//	i++;
		//if (str[i] == '$')
		i++;
	}
}

void	design_cmd(t_arg *pre_cmd, t_simple_cmds *new, t_data *data)
{
	int	i;
	while (pre_cmd)
	{
		i = 0;
		looking_for_expend(pre_cmd->word, *data);
		while (pre_cmd->word[i])
		{
			i++;
		}
		pre_cmd = pre_cmd->next;
	}
	print_data(*data);
	(void) data;
	(void) new;
	(void) pre_cmd;
}
