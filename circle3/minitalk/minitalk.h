#ifndef MINITALK_H
# define MINITALK_H

typedef struct s_node
{
	char c;
	struct s_node *next;
} t_node;

# include "libft.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

#endif
