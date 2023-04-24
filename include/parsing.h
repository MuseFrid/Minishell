/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:47:35 by gduchesn          #+#    #+#             */
/*   Updated: 2023/04/24 14:33:26 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# define UNCLOSED_QUOTE "Error\nSimple or Double quote are not closed\n"
typedef struct s_arg
{
	int		index;
	char	*word;
	int		is_token;
	struct s_arg *next;
}	t_arg;
int	lexer(t_arg *arg, char *str);
#endif
