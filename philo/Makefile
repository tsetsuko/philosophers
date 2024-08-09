CFILES = init.c main.c routine.c time.c utils.c activities.c 
NAME = philosophers
CFLAGS = -Wall -Wextra -Werror -pthread
CC = cc
OFILES = $(CFILES:.c=.o)

all : $(NAME)

$(NAME) : $(OFILES)
	@$(CC) $(CFLAGS) $(OFILES) -o $(NAME)

clean:
	@rm -rf $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all 

.PHONY: all clean fclean re 