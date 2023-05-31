/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 01:18:05 by aabda             #+#    #+#             */
/*   Updated: 2023/05/31 18:55:09 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

//		sources/utils/utils.c
void	ft_init_struct(t_data *data, char **envp);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *str);

//		sources/utils/utils2.c
int		ft_strcmp_strict(const char *s1, const char *s2);
void	ft_free(void **value);

//		sources/utils/path_user_dollar.c
char	*ft_path_and_username(t_data *data);

//		sources/utils/path_user_dollar2.c
char	*ft_catch_user_env(t_data *data);
void	ft_join_pwd_user_dollar(char *user, char *pwd, char *res);
char	*ft_catch_home_by_dir(char *str);

//		sources/utils/env.c
void	ft_replace_value_env(t_env *current, char *value);
char	*ft_catch_key_env(char *value);
char	*ft_catch_value_env(char *value);
t_env	*ft_last_elem_env(t_data *data);

//		sources/utils/env_concat_value.c
void	ft_concat_env(t_data *data, t_env *new, char *value, int equal_index);

//		sources/utils/env_new_node.c
void	ft_new_node_env(t_data *data, t_env *new, char *val);

//		sources/utils/builtins.c
int		ft_check_builtins(t_data *data);

#endif
