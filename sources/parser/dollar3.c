/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 21:58:19 by aabda             #+#    #+#             */
/*   Updated: 2023/06/22 23:11:23 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	**ft_create_tab_env(t_env *cur, char **words, char **w_p, int len)
// {
// 	t_env	*first;
// 	int		i;

// 	first = cur;
// 	w_p = malloc(sizeof(char *) * (len + 1));
// 	if (!w_p)
// 		exit(EXIT_FAILURE);		//	call error function
// 	w_p[len] = NULL;
// 	i = -1;
// 	len = 0;
// 	while (words && words[++i])
// 	{
// 		while (cur)
// 		{
// 			if (ft_strcmp_strict(cur->key, words[i]) == 0)
// 			{
// 				w_p[len] = cur->value;
// 				++len;
// 				break ;
// 			}
// 			cur = cur->next;
// 		}
// 		cur = first;
// 	}
// 	return (w_p);
// }

char	*ft_dollar_to_env(t_data *data, char *str, char **words, int *i_dollar)
{
	// (void)str;
	// char	**words_processed;
	// t_env	*current;
	// int		len;

	// current = data->env;
	// if (!current)
	// 	exit(EXIT_FAILURE);		//	call error function
	// words_processed = NULL;
	// len = -1;
	// while (i_dollar[++len] >= 0)
	// 	;
	// len = i_dollar[len] * -1;
	// words_processed = ft_create_tab_env(current, words, words_processed, len);
	// for (int i = 0; words_processed[i]; i++)
	// 	printf("%s\n", words_processed[i]);
	// return (NULL);

	
	(void)data;
	(void)str;
	(void)i_dollar;
	for (int j = 0; words[j]; j++)
		printf("%s\n", words[j]);
	return (NULL);
}
