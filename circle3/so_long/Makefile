NAME = so_long

SRCS =  testing.c window.c checkmap.c ./srcsGNL/get_next_line.c ./srcsGNL/get_next_line_utils.c


OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -f

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lmlx -lXext -lX11 -lm -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

