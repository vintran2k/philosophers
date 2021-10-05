# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vintran <vintran@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/01 18:05:53 by vintran           #+#    #+#              #
#    Updated: 2021/10/05 17:17:08 by vintran          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	philo
SRCS_DIR			=	./srcs/
HEADER				=	./inc/philo.h
SRCS				=	main.c			\
						init.c			\
						utils.c			\
						thread.c		\
						activity.c		\
						print.c
SRCS_BASENAME		=	$(addprefix $(SRCS_DIR), $(SRCS))
OBJS				=	$(SRCS_BASENAME:.c=.o)
CC					=	clang
FLAGS				=	-Wall -Wextra -Werror -I ./inc/

.c.o			:
				$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all				:	$(NAME)

$(NAME)			:	$(OBJS) $(HEADER)
				$(CC) $(FLAGS) $(OBJS) -o $(NAME) -lpthread
				@echo [$(NAME)] : Created !

clean			:
				rm -f $(OBJS)
				@echo [.o] : Deleted !

fclean			:	clean
				rm -f $(NAME)
				@echo [$(NAME)] : Deleted !

re				:	fclean all

.PHONY: 		clean fclean all re

#valgrind --tool=helgrind ./philo 4 410 200 200