/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 01:18:05 by aabda             #+#    #+#             */
/*   Updated: 2023/05/16 23:47:01 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	ft_init_struct(t_data *data, char **envp);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *str);
int		ft_check_builtins(t_data *data);
void	ft_concat_env(t_data *data, char *value, int equal_index);
void	ft_new_node_env(t_data *data, t_env *current, t_env *new, char *val);
void	ft_replace_value_env(t_env *current, char *value);

#endif
