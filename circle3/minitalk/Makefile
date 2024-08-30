NAME1 = server
NAME2 = client

SRCS1 = server.c
OBJS1 = $(SRCS1:.c=.o)

SRCS2 = client.c
OBJS2 = $(SRCS2:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -L. -lft
RM = rm -f

$(NAME1): $(OBJS1)
	$(CC) $(CFLAGS) $(OBJS1) -o $(NAME1) $(LDFLAGS)

$(NAME2): $(OBJS2)
	$(CC) $(CFLAGS) $(OBJS2) -o $(NAME2) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME1) $(NAME2)

clean:
	$(RM) $(OBJS1) $(OBJS2)

fclean: clean
	$(RM) $(NAME1) $(NAME2)

re: fclean all

.PHONY: all clean fclean re
