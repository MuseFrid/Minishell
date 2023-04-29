/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:30:38 by gduchesn          #+#    #+#             */
/*   Updated: 2023/04/28 23:12:34 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_simple_cmds
{
	char					**str;
	// int						(*builtin)(t_tools *, struct s_simple_cmds *);
	int						num_redirections;
	char					*hd_file_name;
	t_arg					*redirections;
	t_arg					*test_red;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

void			parser(t_arg *arg, t_data data);
void			lst_add_back_cmds(t_simple_cmds **head, t_simple_cmds *new);
void			lst_clear_cmds(t_simple_cmds *head);
void			lst_unlink_arg(t_arg *arg);
t_simple_cmds	*lst_new_cmds(t_arg *arg, int i);

#endif
