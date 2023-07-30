/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 05:13:50 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/29 19:34:42 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_fail(char *to_free, char *to_free2)
{
	free(to_free);
	free(to_free2);
	write_error("Minishell: not able to expand ~\n", NULL, NULL, NULL);
	g_ret_val = 1;
	return (NULL);
}

static char	*replace_tilde(char *word, int *index)
{
	char	*tmp;
	char	*home;
	char	*str;

	tmp = ft_strndup(word, *index);
	home = getenv("HOME");
	if (!home)
		return (get_env_fail(tmp, word));
	str = ft_strjoin(tmp, home);
	free(tmp);
	if (word[(*index) + 1])
		tmp = ft_substr(word, (*index) + 1, (ft_strlen(word) - ((*index) + 1)));
	else
		tmp = ft_strdup("");
	home = ft_strjoin(str, tmp);
	free(str);
	free(tmp);
	free(word);
	*index = 0;
	return (home);
}

void	ft_tilde_expander(t_simple_cmds *cmds, t_arg *pre_cmd)
{
	int		i;
	char	type_q;

	i = 0;
	while (pre_cmd->word[i])
	{
		if (pre_cmd->word[i] == '~')
			pre_cmd->word = replace_tilde(pre_cmd->word, &i);
		if (!pre_cmd->word)
		{
			cmds->end = 1;
			return ;
		}
		if (pre_cmd->word[i]
			&& (pre_cmd->word[i] == '\"' || pre_cmd->word[i] == '\''))
		{
			type_q = pre_cmd->word[i++];
			while (pre_cmd->word[i] != type_q)
				++i;
		}
		++i;
	}
}
