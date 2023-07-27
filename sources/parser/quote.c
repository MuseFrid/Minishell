/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:31:25 by aabda             #+#    #+#             */
/*   Updated: 2023/07/27 20:51:02 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_quoted_string(t_dollar *dollar, char *new_str, int *i, int *j)
{
	char	check;

	check = dollar->str[*j];
	while (dollar->str[++(*j)] != check)
	{
		printf("%s%c%s", GREEN, dollar->str[*j], RESET);
		new_str[*i] = dollar->str[*j];
		++(*i);
	}
		printf("%s%c%s", RED, dollar->str[*j], RESET);
	++(*j);
}

void	ft_str_without_quote(t_dollar *dollar, int len)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = malloc(sizeof(char) * len + 1);
	if (!new_str)
		kill_mini("Minishell");
	i = 0;
	j = 0;
	while (j < len)
	{
		if (dollar->str[j] == '\'' || dollar->str[j] == '"')
			copy_quoted_string(dollar, new_str, &i, &j);
		else
		{
			printf("%s%c%s", MAGENTA, dollar->str[j], RESET);
			new_str[i] = dollar->str[j];
			++i;
			++j;
		}
	}
	new_str[i] = '\0';
	ft_free((void **)&dollar->str);
	dollar->str = new_str;
	printf("\n");
}

