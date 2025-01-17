NAME = philo

SRCS = philo.c ft_atoi.c ft_itoa.c test.c

BOBJS = $(BSRCS:.c=.o)

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=undefined -pthread

RM = rm -f

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

