/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:25:25 by marsenij          #+#    #+#             */
/*   Updated: 2024/08/25 14:28:28 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_node *g_char_list = NULL;

t_node *create_node(char c)
{
	t_node *new_node;
	
	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return NULL;
	new_node->c = c;
	new_node->next = NULL;
	return new_node;
}

void append_node(t_node **head, char c)
{
	t_node *new_node;
	t_node *current;
	
	new_node = create_node(c);
	current = *head;
	if (!new_node)
	    return;
	if (!*head)
	{
		*head = new_node;
		return;
	}
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void writeall(void)
{
	t_node *current;
	t_node *tmp;
	
	current = g_char_list;
	while (current)
	{
		write(1, &current->c, 1);
		tmp = current;
		current = current->next;
		free(tmp);
	}
	g_char_list = NULL;
}

void	sighandler(int signal)
{
	static int	i;
	static char	c;

	if (signal == SIGUSR1)
		c = c << 1;
	else if (signal == SIGUSR2)
		c = c << 1 | 0b00000001;
	i++;
	if (i == 8)
	{
		if(c == 0)
			writeall();
		append_node(&g_char_list, c);
		i = 0;
		c = 0;
	}
}

int main(void)
{
	int			pid;
	struct sigaction	sa;
	char			*pid_str;

	pid = getpid();
	sa.sa_handler = sighandler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid_str = ft_itoa(pid);
	write(1, pid_str, ft_strlen(pid_str));
	while (1)
	{
		pause();
	}
	free(pid_str);
	return 0;
}
