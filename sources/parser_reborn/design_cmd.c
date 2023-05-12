/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:37:19 by gduchesn          #+#    #+#             */
/*   Updated: 2023/05/12 14:15:33 by gduchesn         ###   ########.fr       */
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

int	get_dollar_word(char *str, int i)
{
	while (str[i])
	{
		if (is_token(str, &i, 0) || str[i] == ' ')
			break;
		i++;
	}
	return (i);
}

char	*env_variable(char *str, int tmp, t_env env)
{
	while (env)
	{
		if (!ft_strncmp(str, env->key, tmp))
			return (ft_strdup(env->line));
		env = env->next;
	}
	return (NULL);
}

void	handle_quotes(char *str, int tmp, int *i, t_data data)
{
	char	stop;
	int		tmp;
	char 	*dollard;//after_get_dollard_value
	char	*quote_content;

	stop = str[(*i)++];
	dollard = NULL;
	while (str[*i] != stop)
	{
		if (tmp == DOUBLE_QUOTES && str[*i] == '$')
		{
			tmp = get_dollar_word(str, *i);
			dollard = env_variable((str + *i), tmp, data->env);
			*i += tmp;
		};
	}
	(void) data;
	(void) str;
	(void) tmp;
	return (quote_content);
}

char	*looking_for_expend(char *str, t_data data)
{
	int	i;
	int	tmp;
	int	start;
	char	*final_str;

	i = 0;
	tmp = 0;
	start = i;
	final_str = NULL;
	while (str[i])
	{
		tmp = is_interaction(str[i]);
		if (tmp && tmp != DOLLAR)
		{
			final_str = parsing_strjoin(final_str, ft_substr(str, start, i - start));
			start = i + 1;
			//final_str = parsing_strjoin(final_str, handle_quotes(str, tmp, &i, data));
			//start = i;
		}
		i++;
	}
}

void	design_cmd(t_arg *pre_cmd, t_simple_cmds *new, t_data *data)
{
	int	i;

	i = 0;
	while (pre_cmd)
	{
		new->str[i++] = looking_for_expend(pre_cmd->word, *data);
		pre_cmd = pre_cmd->next;
	}
	print_data(*data);
	(void) data;
	(void) new;
	(void) pre_cmd;
}
