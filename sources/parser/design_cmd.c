/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:31:02 by gduchesn          #+#    #+#             */
/*   Updated: 2023/06/14 18:03:53 by aabda            ###   ########.fr       */
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

char	*getend(char *str, int start, char **final_str, t_env *env)
{
	int	i;

	return (NULL);
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

char	*get_simple_q(char **str, int i, char *allreadyclean)
{
	int		start;
	char	*in_quotes;
	char	*tmp;

	start = ++i;
	while ((*str)[i] && (*str)[i] != '\'')
		i++;
	printf("i = %d / start = %d\n", i, start);
	in_quotes = ft_substr(*str, start, i - start);
	tmp = ft_substr(*str, i, ft_strlen(*str) - i);
	free(*str);
	//*str = NULL;
	*str = tmp;
	printf("str == %p\n", *str);
	printf("in_quotes : %s\n", in_quotes);
	printf("allreadyclean : %s\n", allreadyclean);
	tmp = ft_strjoin(allreadyclean, in_quotes);
	printf("*str = %p / tmp = %s\n", *str, tmp);
	ft_free((void **)&in_quotes);
	ft_free((void **)&allreadyclean);
	return (tmp);
}

char	*expand_env(char *str, t_data data, char **final_str)
{
	int		i;
	char	*allreadyclean;
	
	i = 0;
	allreadyclean = NULL;
	(void) final_str;
	(void) data;
	while (str && str[i])
	{
		// printf("str devant la boucle == %s\n", str);
		// printf("je suis la 2 fois\n");
		if (str[i] == '\'' || str[i] == '\"' || str[i] == '$')
		{
		// printf("je suis la 2 fois\n");
			allreadyclean = ft_strldup(str, i);
			// printf("ah %s\n", allreadyclean);
			if (str[i] == '\'')
				allreadyclean = get_simple_q(&str, i, allreadyclean);
			//getend(str, i, final_str, data.env);
			i = 0;
			// printf("str == %s\n", str);
		}
		i++;
	}
	if (allreadyclean)
		return (ft_strjoin(allreadyclean, str));
	return (str);
}

char	*clean_cmd(char *str, t_data data)
{
	char	*after_expand;

	after_expand = NULL;
	expand_env(str, data, &after_expand);
	exit(0);
	//ft_free((void **) str);
	return (NULL);
}

void	design_cmd(t_arg *pre_cmd, t_simple_cmds *new, t_data *data)
{
	int	i;

	i = 0;
	while (pre_cmd)
	{
		// printf("%s\n", pre_cmd->word);
		new->tab[i++] = clean_cmd(pre_cmd->word, *data);
		pre_cmd = pre_cmd->next;
	}
	//print_data(*data);
	(void) data;
	(void) new;
	(void) pre_cmd;
}
