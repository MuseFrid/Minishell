/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:11:21 by gduchesn          #+#    #+#             */
/*   Updated: 2023/05/08 15:45:32 by gduchesn         ###   ########.fr       */
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
# include "lexer.h"
# include "color.h"
# include "core.h"
# include "parser.h"
# include "env.h"
# include "utils.h"

# define SUCCESS 0
# define FAIL 1

int		ga_error(char *error_msg);

#endif
