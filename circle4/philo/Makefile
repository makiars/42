NAME = philo

SRCS = philo.c ft_atoi.c ft_itoa.c thread.c time.c routine.c monitor.c ./ft_printf/ft_printf.c ./ft_printf/ft_putnbr.c ./ft_printf/ft_putchar.c ./ft_printf/ft_putstr.c ./ft_printf/ft_putnbr_unsigned.c ./ft_printf/ft_puthex.c ./ft_printf/ft_putptr.c

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

