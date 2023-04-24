/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:44:02 by gduchesn          #+#    #+#             */
/*   Updated: 2023/04/24 15:40:53 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/parsing.h"

t_arg	*lst_new_arg(char *str, int i, int j, int index)
{
	t_arg	*new;
	int	k;

	k = 0;
	new = malloc(sizeof(t_arg));
	if (!new)
		exit(1);
	new->word = malloc(sizeof(char) * (j + 1));
	if (!new->word)
		exit(1);
	new->word[j + 1] = '\0';
	while (i - j - 1 < i)
	{
		if (!str[i - j])
			break ;
		new->word[k++] = str[i - j];
		j--;
	}
	new->index = index;
	new->is_token = 0;
	new->next = NULL;
	return (new);
}

void	lst_add_arg(t_arg **arg, t_arg *new)
{
	t_arg	*snake;

	if (!new)
		return ;
	if (*arg)
	{
		snake = *arg;
		while (snake->next)
			snake = snake->next;
		snake->next = new;
	}
	else
		*arg = new;
}

void	lst_clear_arg(t_arg *arg)
{
	t_arg	*to_free;

	if (!arg)
		return ;
	while (arg)
	{
		to_free = arg;
		arg = arg->next;
		free(to_free->word);
		free(to_free);
	}
}

int	quote(char *str, int *i, int *j, char to_find)
{
	while (1)
	{
		(*i)++;
		(*j)++;
		if (!(str[*i] != to_find && str[*i]))
			break ;
	}
	if (!str[*i])
		return (ga_error(UNCLOSED_QUOTE));
	return (SUCCESS);
}

int	lexer(t_arg *arg, char *str)
{
	int	i;
	int	j;
	int	index;
	t_arg	*new;

	i = 0;
	index = 0;
	while (1)
	{
		j = 0;
		while (str[i] == ' ')
			i++;
		while (str[i] != ' ' && str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				printf("we are in\n");
				printf("%d\n", i);
				if (quote(str, &i, &j, str[i]))
				{
					printf("c\'est ici\n");
					exit(1);
				}
				printf("%d\n", i);
			}
			i++;
			j++;
		}
		new = lst_new_arg(str, i, j, index++);
		lst_add_arg(&arg, new);
		if (!str[i])
			break ;
	}
	while (arg)
	{
		printf("%s\n", arg->word);
		arg = arg->next;
	}
	lst_clear_arg(arg);
	return (SUCCESS);
}

/*int	main()
{
	parsing(NULL, "je sui's un pipe");
}*/
