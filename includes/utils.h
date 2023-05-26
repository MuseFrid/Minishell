/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 01:18:05 by aabda             #+#    #+#             */
/*   Updated: 2023/05/26 15:29:38 by gduchesn         ###   ########.fr       */
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
int		ft_cmp_str_strict(const char *s1, const char *s2);
void	ft_free(void *value);

//		sources/utils/env.c
void	ft_replace_value_env(t_env *current, char *value);
char	*ft_catch_key_env(char *value);
char	*ft_catch_value_env(char *value);

//		sources/utils/env_concat_value.c
void	ft_concat_env(t_data *data, t_env *new, char *value, int equal_index);

//		sources/utils/env_new_node.c
void	ft_new_node_env(t_data *data, t_env *current, t_env *new, char *val);

//		sources/utils/builtins.c
int		ft_check_builtins(t_data *data);

//		source/utils/free_all.c
void	free_env(t_env *env);
void	free_all(t_data *data);

#endif
