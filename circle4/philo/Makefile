NAME = philo

SRCS = routine2.c thread2.c init_philo.c init.c philo.c ft_atoi.c ft_itoa.c thread.c time.c routine.c monitor.c

BOBJS = $(BSRCS:.c=.o)

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread -fno-omit-frame-pointer  -pthread

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

