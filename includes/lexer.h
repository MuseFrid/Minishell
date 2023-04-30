/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:35:11 by gduchesn          #+#    #+#             */
/*   Updated: 2023/04/28 01:49:38 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# define UNCLOSED_QUOTE "Error\nSimple or Double quote are not closed\n"

typedef enum e_token
{
	NOT_A_TOKEN,
	PIPE,
	GREATER,
	D_GREATER,
	LOWER,
	D_LOWER
}	t_token;

typedef struct s_arg
{
	int				index;
	char			*word;
	t_token			is_token;
	struct s_arg	*next;
	struct s_arg	*previous;
}	t_arg;

t_arg	*lexer(t_arg *arg, char *str);
t_arg	*lst_new_arg(char *new_word, int token, int index);
void	lst_add_arg(t_arg **arg, t_arg *new);
void	lst_clear_arg(t_arg *arg);
void	set_previous(t_arg *arg);

#endif