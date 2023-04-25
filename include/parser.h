/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:30:38 by gduchesn          #+#    #+#             */
/*   Updated: 2023/04/25 17:59:27 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
void	parser(t_arg *arg, t_data data);

typedef struct s_simple_cmds
{
	char **str;
	//int (*builtin)(t_tools *, struct s_simple_cmds *);
	int num_redirections;
	char *hd_file_name;
	t_arg *redirections;
	struct s_simple_cmds *next;
	struct s_simple_cmds *prev;
}	t_simple_cmds;

#endif
