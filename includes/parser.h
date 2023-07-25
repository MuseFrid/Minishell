/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:30:38 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/25 15:13:31 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
//# define DOLLAR 3
//# define DOUBLE_QUOTES 2

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
	t_arg					*redirections;
	t_arg					*test_red;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

typedef struct s_bool
{
	int	simple_q;
	int	double_q;
}	t_bool;

typedef struct s_dollar
{
	char	*str;
	// char	*is_quote;
	char	**words;
	int		*i_dollar;
	int		quote[2];
}	t_dollar;

void			design_cmd(t_arg *pre_cmd, t_simple_cmds *new, t_data *data);
t_simple_cmds	*parser(t_arg *arg, t_data *data);
void			lst_add_back_cmds(t_simple_cmds **head, t_simple_cmds *new);
void			lst_clear_cmds(t_simple_cmds *head);
void			lst_unlink_arg(t_arg *arg);
void			lst_new_cmds(t_simple_cmds **new);
char			*parsing_strjoin(char const *s1, char const *s2);
void			print_parser(t_simple_cmds *cmds);
void			print_tab(t_simple_cmds *cmds);
char			*ft_dollar_handling(t_data *data, t_dollar *dollar, t_arg *pre_cmd);
char			*ft_replace_dollar_by_env(t_data *data, t_dollar *dollar, t_arg *pre_cmd);
char			*ft_dollar_to_env(t_data *data, t_dollar *dollar, t_arg *pre_cmd);
void			ft_join_p_word(t_dollar *dollar, char **process, char *word);
void			ft_str_without_quote(t_dollar *dollar, int len);

#endif
