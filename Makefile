# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 23:26:47 by gduchesn          #+#    #+#              #
#    Updated: 2023/05/08 17:23:28 by gduchesn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
FLAGS = -Wall -Werror -Wextra -fsanitize=address -g
LIBRARIES = -lreadline
INCLUDES = -I$(HEADERS_D)
REMOVE = rm -Rf
.PHONY: all clean fclean re

HEADERS = $(addprefix $(HEADERS_D), $(HEADERS_LIST))
HEADERS_D = ./includes/
HEADERS_LIST = minishell.h

SOURCES = $(addprefix $(SOURCES_D), $(SOURCES_LIST))
SOURCES_D = ./sources/
SOURCES_LIST = main.c \
			   utils.c \
			   ga_error.c \
			   $(LEXER) \
			   $(PARSER) \
			   $(ENV)

LEXER = $(addprefix $(LEXER_D), $(LEXER_LIST))
LEXER_D = lexer/
LEXER_LIST = lst_lexer.c \
			 lexer.c

PARSER = $(addprefix $(PARSER_D), $(PARSER_LIST))
PARSER_D = parser_reborn/
PARSER_LIST = parser.c \
			  lst_parser.c \
			  design_cmd.c \
			  parsing_strjoin.c

ENV= $(addprefix $(ENV_D), $(ENV_LIST))
ENV_D = env/
ENV_LIST = getenv.c \
	   env_-i.c

#"what is in new directory" = $(addprefix "directory", $("list"))
#"new list .c" = "new (.c)"

OBJECTS = $(addprefix $(OBJECTS_MAIN_D), $(OBJECTS_LIST))
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS_MAIN_D = objects/
OBJECTS_CREATE_D = $(OBJECTS_MAIN_D) $(addprefix $(OBJECTS_MAIN_D), $(OBJECTS_SUB_D))
OBJECTS_SUB_D = $(LEXER_D) $(PARSER_D) $(ENV_D)

all: $(NAME)

$(NAME): $(OBJECTS_MAIN_D) $(OBJECTS)
		$(CC) $(FLAGS) $(INCLUDES) $(OBJECTS) -o $(NAME) $(LIBRARIES)

$(OBJECTS_MAIN_D):
	mkdir -p $(OBJECTS_CREATE_D)

$(OBJECTS_MAIN_D)%.o : $(SOURCES_D)%.c $(HEADERS)
	$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@

clean:
	$(REMOVE) $(OBJECTS_MAIN_D)

fclean: clean
	$(REMOVE) $(NAME)

re: fclean all

#-fsanitize=address -g
