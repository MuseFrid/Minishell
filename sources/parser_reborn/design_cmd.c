/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:31:02 by gduchesn          #+#    #+#             */
/*   Updated: 2023/05/31 16:47:07 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_variable(char *str, int tmp, t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(str, env->key, tmp))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

void	bool_init(t_bool *bool_quotes)
{
	bool_quotes->simple_q = 0;
	bool_quotes->double_q = 0;
}

void	change_bool_value(int *bool_v)
{
	if (*bool_v == 0)
		*bool_v = 1;
	else if (*bool_v == 1)
		*bool_v = 0;
}

char	*getend(char *str, int start, char **final_str, t_env *env)
{
	int	i;

	i = start;
	*final_str = ft_substr(str, 0, start);
	printf("%s\n", *final_str);
	while (1)
	{
		i++;
		if (is_token(str, &i, 0) || str[i] == ' ' || !str[i])
		{
			while (env && strncmp((str + start + 1), env->key, i - start - 1))
				env = env->next;
			printf("%s\n", env->key);
			printf("out\n");
			break ;
		}
	}
	printf("%s\n", str);
	if (str[i])
		str = ft_substr(str, i, (ft_strlen(str) - i));
	else
		str = NULL;
	printf("%s\n", str);
	return (str);
}

void	expand_env(char *str, t_data data, char **final_str)
{
	int	i;
	t_bool	bool_quotes;

	(void) data;
	i = 0;
	bool_init(&bool_quotes);
	while (str && str[i++])
	{
		if (str[i] == '\'' && bool_quotes.double_q == 0)
			change_bool_value(&bool_quotes.simple_q);
		if (str[i] == '\"' && bool_quotes.simple_q == 0)
			change_bool_value(&bool_quotes.double_q);
		if (str[i] == '$' && bool_quotes.simple_q == 0)
		{
			str = getend(str, i, final_str, data.env);
			i = 0;
		}
	}
}

char	*clean_cmd(char *str, t_data data)
{
	char	*after_expand;

	after_expand = NULL;
	expand_env(str, data, &after_expand);
	//ft_free((void **) str);
	return (NULL);
}

void	design_cmd(t_arg *pre_cmd, t_simple_cmds *new, t_data *data)
{
	int	i;

	i = 0;
	while (pre_cmd)
	{
		printf("%s\n", pre_cmd->word);
		new->tab[i++] = clean_cmd(pre_cmd->word, *data);
		pre_cmd = pre_cmd->next;
	}
	//print_data(*data);
	(void) data;
	(void) new;
	(void) pre_cmd;
}
