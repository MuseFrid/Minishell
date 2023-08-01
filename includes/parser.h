/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:30:38 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/31 20:21:52 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define END_VAR_ENV ":;&|<>(){}[]\"'!^$#@*?%+=/\\`~ "

enum e_parsing
{
	SIMPLE_QUOTE = 1,
	DOUBLE_QUOTES,
	DOLLAR
};

typedef struct s_simple_cmds
{
	char					**tab;
	int						(*builtin)(struct s_data *);
	int						pid;
	int						end;
	t_arg					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

typedef struct s_dollar
{
	char	*str;
	char	**words;
	int		*i_dollar;
	int		quote[2];
}	t_dollar;

void			design_cmd(t_arg **pre_cmd,
					t_simple_cmds *new, t_data *data, t_arg *redirections);
t_simple_cmds	*parser(t_arg *arg,
					t_data *data, t_simple_cmds *cmds, t_arg *pre_cmd);
void			lst_add_back_cmds(t_simple_cmds **head,
					t_simple_cmds *new);
void			*lst_clear_cmds(t_simple_cmds **head);
int				lst_size_arg(t_arg *pre_cmd);
void			lst_unlink_arg(t_arg *arg);
void			lst_new_cmds(t_simple_cmds **new);
char			*parsing_strjoin(char const *s1, char const *s2);
void			print_parser(t_simple_cmds *cmds);
void			print_tab(t_simple_cmds *cmds);
char			*ft_dollar_handling(t_data *data,
					t_dollar *dollar, t_arg *pre_cmd);
char			*ft_replace_dollar_by_env(t_data *data,
					t_dollar *dollar, t_arg *pre_cmd);
char			*ft_dollar_to_env(t_data *data,
					t_dollar *dollar, t_arg *pre_cmd);
void			ft_join_p_word(t_dollar *dollar, char **process, char *word);
void			ft_str_without_quote(t_dollar *dollar, int len);
char			*free_dollar_struct(t_dollar *dollar);
void			ft_word_str(char *str, char *word, int *i);
void			ft_start_str(t_dollar *dollar, char *str, int *i, int index);
void			ft_tilde_expander(t_simple_cmds *cmds, t_arg *pre_cmd);
char			*ft_escape_first_digit(t_dollar *dollar, int index);
int				ft_size_i_dollar(t_dollar *dollar);

#endif
