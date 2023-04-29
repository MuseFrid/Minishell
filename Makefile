# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabda <aabda@student.s19.be>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 13:36:56 by aabda             #+#    #+#              #
#    Updated: 2023/04/29 00:31:41 by aabda            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
DIR		= srcs/
CC		= gcc
FLAGS	= -Wall -Wextra -Werror

SRCS = $(DIR)builtins/ft_env.c $(DIR)builtins/ft_exit.c \
	$(DIR)builtins/ft_pwd.c \
	$(DIR)builtins/ft_unset.c $(DIR)env/getenv.c \
	$(DIR)utils/libft_utils.c $(DIR)utils/utils.c \
	$(DIR)core/minishell.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) -lreadline

norm:
	norminette -R CheckDefine

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re norm