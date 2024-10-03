# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 14:14:03 by zogorzeb          #+#    #+#              #
#    Updated: 2024/10/03 14:32:54 by zogorzeb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES = init.c main.c routine.c \
		 activities.c \
		 monitor.c \
		 get_and_set.c \
		 utils/ft_atol.c \
		 utils/utils.c \
		 utils/time.c
NAME = philo
CFLAGS = -Wall -Wextra -Werror -pthread
CC = cc
OFILES = $(CFILES:.c=.o)

all : $(NAME)

$(NAME) : $(OFILES)
	@$(CC) $(CFLAGS) $(OFILES) -o $(NAME)
	make clean

clean:
	@rm -rf $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all 

.PHONY: all clean fclean re 

valid_test:
	$(CC) $(CFLAGS) unity/src/unity.c test/validation_test.c utils.c utils/error.c utils/ft_atoi.c utils/ft_atol.c