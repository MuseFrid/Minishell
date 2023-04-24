# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 23:26:47 by gduchesn          #+#    #+#              #
#    Updated: 2023/04/24 14:41:09 by gduchesn         ###   ########.fr        #
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
			   parsing.c \
			   ga_error.c

#"what is in new directory" = $(addprefix "directory", $("list"))
#"new list .c" = "new (.c)"

OBJECTS = $(addprefix $(OBJECTS_MAIN_D), $(OBJECTS_LIST))
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS_MAIN_D = objects/
OBJECTS_CREATE_D = $(OBJECTS_MAIN_D) #$(addprefix $(OBJECTS_MAIN_D), $(OBJECTS_SUB_D))
#OBJECTS_SUB_D = #"sub directory"

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
