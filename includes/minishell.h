/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:11:21 by gduchesn          #+#    #+#             */
/*   Updated: 2023/08/01 04:19:54 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include <signal.h>
# include <limits.h>
# include <sys/wait.h>
# include "lexer.h"
# include "color.h"
# include "core.h"
# include "parser.h"
# include "builtins.h"
# include "env.h"
# include "utils.h"
# include "executor.h"
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCESS 0
# define FAIL 1

#endif
