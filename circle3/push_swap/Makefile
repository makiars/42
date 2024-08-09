NAME = push_swap

SRCS =  testing.c ft_strcmp.c ft_strlcpy.c ft_strtrim.c algorithm.c ft_itoa.c helper.c nodeinfo.c push_swap.c rotate.c ft_atoi.c ft_split.c nodeinfo2.c push.c reverse_rotate.c swap.c

BOBJS = $(BSRCS:.c=.o)

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

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

