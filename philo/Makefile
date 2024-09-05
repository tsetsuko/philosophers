CFILES = init.c main.c routine.c time.c utils.c activities.c monitor.c get_and_set.c utils/error.c \
		 utils/ft_atol.c 
NAME = philosophers
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