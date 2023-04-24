/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:11:21 by gduchesn          #+#    #+#             */
/*   Updated: 2023/04/24 17:36:30 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include <signal.h>
# include "color.h"
# include "lexer.h"
# define SUCCESS 0
# define FAIL 1

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *str);
char	*parse(char **envp, const char *cmd);
int		ga_error(char *error_msg);

#endif
