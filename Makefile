# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabda <aabda@student.s19.be>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 23:26:47 by gduchesn          #+#    #+#              #
#    Updated: 2023/06/14 16:27:50 by aabda            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
FLAGS = -Wall -Werror -Wextra -fsanitize=address -g
LDFLAGS = -L/opt/homebrew/opt/readline/lib
CPPFLAGS = -I/opt/homebrew/opt/readline/include
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
CORE_LIST = minishell.c signal.c

BUILTINS = $(addprefix $(BUILTINS_D), $(BUILTINS_LIST))
BUILTINS_D = builtins/
BUILTINS_LIST = ft_cd.c ft_echo.c \
	ft_env.c ft_exit.c \
	ft_export.c ft_pwd.c \
	ft_unset.c

UTILS = $(addprefix $(UTILS_D), $(UTILS_LIST))
UTILS_D = utils/
UTILS_LIST = utils.c ga_error.c \
	builtins.c env.c \
	env_new_node.c env_concat_value.c \
	utils2.c path_user_dollar.c \
	path_user_dollar2.c  free.c \
	libft_utils.c libft_utils2.c

LEXER = $(addprefix $(LEXER_D), $(LEXER_LIST))
LEXER_D = lexer/
LEXER_LIST = lst_lexer.c \
			 lexer.c

PARSER = $(addprefix $(PARSER_D), $(PARSER_LIST))
PARSER_D = parser_reborn/
PARSER_LIST = parser.c \
			  lst_parser.c \
			  parsing_strjoin.c design_cmd.c

ENV= $(addprefix $(ENV_D), $(ENV_LIST))
ENV_D = env/
ENV_LIST = getenv.c env_-i.c \
	underscore.c

EXECUTOR= $(addprefix $(EXECUTOR_D), $(EXECUTOR_LIST))
EXECUTOR_D=executor/
EXECUTOR_LIST= heredoc_handler.c redirection_hub.c

#"what is in new directory" = $(addprefix "directory", $("list"))
#"new list .c" = "new (.c)"

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

#-fsanitize=address -g
