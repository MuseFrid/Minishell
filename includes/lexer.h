/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:35:11 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/26 17:22:00 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# define UNCLOSED_QUOTE "Error\nSimple or Double quote are not closed\n"

enum e_token
{
	NOT_A_TOKEN = 0,
	PIPE,
	GREATER,
	D_GREATER,
	LOWER,
	D_LOWER
};

typedef struct s_arg
{
	char			*word;
	int				is_token;
	struct s_arg	*next;
}	t_arg;

int		is_token(char *str, int *i, int able_touch_i);
t_arg	*lexer(t_arg *arg, char *str);
t_arg	*lst_new_arg(char *new_word, int token);
void	lst_add_arg(t_arg **arg, t_arg *new);
void	lst_clear_arg(t_arg *arg);
void	set_previous(t_arg *arg);

#endif
