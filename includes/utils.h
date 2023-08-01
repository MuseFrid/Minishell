/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 01:18:05 by aabda             #+#    #+#             */
/*   Updated: 2023/08/01 04:20:29 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

//      sources/utils/ga_error.c
int		ga_error(char *error_msg);

//		sources/utils/ft_split.c
char	**ft_split(char const *s, char c);

//		sources/utils/builtins.c
int		ft_check_builtins(t_data *data);

//		sources/utils/env_concat_value.c
void	ft_concat_env(t_data *data, t_env *new, char *value, int equal_index);

//		sources/utils/env_new_node.c
void	ft_new_node_env(t_data *data, t_env *new, char *val);

//		sources/utils/env.c
t_env	*ft_last_elem_env(t_data *data);
void	ft_replace_value_env(t_env *current, char *value);
char	*ft_catch_key_env(char *value);
char	*ft_catch_value_env(char *value);

//		sources/utils/free.c
void	free_all(t_data *data);
void	free_env(t_env *env);
void	ft_free(void **value);
void	free_before_new_cmds(t_data *data, char *str);
char	*free_access(char **tab, char *cmd);

//		sources/utils/ga_error.c
int		ga_error(char *error_msg);
int		write_error(char *prt1, char *prt2, char *prt3, char *prt4);
void	cmds_is_finish(t_simple_cmds *cmds);
void	kill_mini(char *error_msg);

//		sources/utils/libft_utils.c
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);

//		sources/utils/libft_utils2.c
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *str);
int		ft_atoi(const char *str);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strndup(const char *str, int n);

//		sources/utils/libft_utils3.c
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);

//		sources/utils/path_user_dollar.c
char	*ft_path_and_username(t_data *data);

//		sources/utils/path_user_dollar2.c
void	ft_join_pwd_user_dollar(char *user, char *pwd, char *res);

//		sources/utils/utils.c
void	ft_init_struct(t_data *data, char **envp);

//		sources/utils/utils2.c
int		ft_strcmp_strict(const char *s1, const char *s2);
char	*ft_get_value_env(t_data *data, char *key);
int		ft_count_slash(char *str);
char	*ft_strldup(const char *str, int len);

//		sources/utils/utils3.c
int		ft_count_char_to_end(char *str, int index, char start, char *end);

//		sources/utils/fix_word.c
void	redesign_word(char **word, int *i, char type, int *bool_quotes);
int		fix_word(char **word);

#endif
