# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 23:26:47 by gduchesn          #+#    #+#              #
#    Updated: 2023/08/01 12:30:54 by gduchesn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
FLAGS = -Wall -Werror -Wextra
LDFLAGS = -L$(HOME)/.brew/opt/readline/lib
CPPFLAGS = -I$(HOME)/.brew/opt/readline/include
LIBRARIES = -lreadline
INCLUDES = -I$(HEADERS_D)
REMOVE = rm -Rf
.PHONY: all clean fclean re

HEADERS = $(addprefix $(HEADERS_D), $(HEADERS_LIST))
HEADERS_D = ./includes/
HEADERS_LIST = minishell.h

SOURCES = $(addprefix $(SOURCES_D), $(SOURCES_LIST))
SOURCES_D = ./sources/
SOURCES_LIST = $(LEXER) $(PARSER) \
	$(ENV) $(CORE) \
	$(BUILTINS) $(UTILS) \
	$(EXECUTOR)

CORE = $(addprefix $(CORE_D), $(CORE_LIST))
CORE_D = core/
CORE_LIST = minishell.c signal.c \
			prompt.c

BUILTINS = $(addprefix $(BUILTINS_D), $(BUILTINS_LIST))
BUILTINS_D = builtins/
BUILTINS_LIST = ft_cd.c ft_echo.c \
	ft_env.c ft_exit.c \
	ft_export.c ft_pwd.c \
	ft_unset.c

UTILS = $(addprefix $(UTILS_D), $(UTILS_LIST))
UTILS_D = utils/
UTILS_LIST = ga_error.c \
	builtins.c env.c \
	env_new_node.c env_concat_value.c \
	path_user_dollar.c path_user_dollar2.c \
	libft_utils.c libft_utils2.c libft_utils3.c \
	utils.c utils2.c utils3.c utils4.c \
	ft_split.c kill_mini.c free.c \
	fix_word.c

LEXER = $(addprefix $(LEXER_D), $(LEXER_LIST))
LEXER_D = lexer/
LEXER_LIST = lst_lexer.c \
	lexer.c

PARSER = $(addprefix $(PARSER_D), $(PARSER_LIST))
PARSER_D = parser/
PARSER_LIST = parser.c lst_parser.c \
	design_cmd.c \
	dollar.c dollar2.c dollar3.c dollar4.c \
	quote.c tilde_expander.c

ENV= $(addprefix $(ENV_D), $(ENV_LIST))
ENV_D = env/
ENV_LIST = getenv.c env_-i.c \
	underscore.c

EXECUTOR= $(addprefix $(EXECUTOR_D), $(EXECUTOR_LIST))
EXECUTOR_D=executor/
EXECUTOR_LIST= new_heredoc.c new_heredoc2.c redirection_hub.c \
			   run_all_cmds.c access.c \
			   wait_child.c child_related.c init_and_end_fd.c

OBJECTS = $(addprefix $(OBJECTS_MAIN_D), $(OBJECTS_LIST))
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS_MAIN_D = objects/
OBJECTS_CREATE_D = $(OBJECTS_MAIN_D) $(addprefix $(OBJECTS_MAIN_D), $(OBJECTS_SUB_D))
OBJECTS_SUB_D = $(LEXER_D) $(PARSER_D) $(ENV_D) $(CORE_D) $(UTILS_D) $(BUILTINS_D) $(EXECUTOR)

all: $(NAME)

$(NAME): $(OBJECTS_MAIN_D) $(OBJECTS)
		$(CC) $(FLAGS) $(INCLUDES) $(OBJECTS) $(LDFLAGS) $(CPPFLAGS) $(LIBRARIES) -o $(NAME)

$(OBJECTS_MAIN_D):
	mkdir -p $(OBJECTS_CREATE_D)

$(OBJECTS_MAIN_D)%.o : $(SOURCES_D)%.c $(HEADERS)
	$(CC) $(FLAGS) $(CPPFLAGS) -c $(INCLUDES) $< -o $@

clean:
	$(REMOVE) $(OBJECTS_MAIN_D)

fclean: clean
	$(REMOVE) $(NAME)

re: fclean all
