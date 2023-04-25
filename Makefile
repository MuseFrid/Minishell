# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 23:26:47 by gduchesn          #+#    #+#              #
#    Updated: 2023/04/25 16:41:55 by gduchesn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
FLAGS = -Wall -Werror -Wextra
LIBRARIES = -lreadline
INCLUDES = -I$(HEADERS_D)
REMOVE = rm -Rf
.PHONY: all clean fclean re

HEADERS = $(addprefix $(HEADERS_D), $(HEADERS_LIST))
HEADERS_D = ./include/
HEADERS_LIST = minishell.h

SOURCES = $(addprefix $(SOURCES_D), $(SOURCES_LIST))
SOURCES_D = ./sources/
SOURCES_LIST = main.c \
			   utils.c \
			   ga_error.c \
			   $(LEXER) \
			   $(PARSER) \
			   $(ALEXIS_PART)

LEXER = $(addprefix $(LEXER_D), $(LEXER_LIST))
LEXER_D = lexer/
LEXER_LIST = lst_lexer.c \
			 lexer.c

PARSER = $(addprefix $(PARSER_D), $(PARSER_LIST))
PARSER_D = parser/
PARSER_LIST = parser.c

ALEXIS_PART = $(addprefix $(ALEXIS_PART_D), $(ALEXIS_PART_LIST))
ALEXIS_PART_D = alexis_part/
ALEXIS_PART_LIST = getenv.c

#"what is in new directory" = $(addprefix "directory", $("list"))
#"new list .c" = "new (.c)"

OBJECTS = $(addprefix $(OBJECTS_MAIN_D), $(OBJECTS_LIST))
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS_MAIN_D = objects/
OBJECTS_CREATE_D = $(OBJECTS_MAIN_D) $(addprefix $(OBJECTS_MAIN_D), $(OBJECTS_SUB_D))
OBJECTS_SUB_D = $(LEXER_D) $(PARSER_D) $(ALEXIS_PART_D)

all: $(NAME)

$(NAME): $(OBJECTS_MAIN_D) $(OBJECTS)
		$(CC) $(FLAGS) $(LIBRARIES) $(INCLUDES) $(OBJECTS) -o $(NAME)

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
