/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:31:25 by aabda             #+#    #+#             */
/*   Updated: 2023/07/08 22:54:25 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_quoted_string(t_dollar *dollar, char *new_str, int *i, int *j)
{
	char	check;

	check = dollar->str[*j];
	while (dollar->str[++(*j)] != check)
	{
		new_str[*i] = dollar->str[*j];
		++(*i);
	}
	++(*j);
}

void	ft_str_without_quote(t_dollar *dollar, int len)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = malloc(sizeof(char) * len + 1);
	if (!new_str)
		exit(EXIT_FAILURE);		//	call the error function
	i = 0;
	j = 0;

	while (j < len)
	{
		if (dollar->str[j] == '\'' || dollar->str[j] == '"')
			copy_quoted_string(dollar, new_str, &i, &j);
		else
		{
			new_str[i] = dollar->str[j];
			++i;
			++j;
		}
	}
	new_str[i] = '\0';
	printf("%s\n", new_str);
}

