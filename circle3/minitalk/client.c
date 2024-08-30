/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:25:25 by marsenij          #+#    #+#             */
/*   Updated: 2024/08/25 14:28:28 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile int g_ack_received;

void sig_ack_handler (int signal)
{
	(void) signal;
	g_ack_received = 1;
}
void	send(int pid, char *str)
{
	int		i;
	char		c;
	struct sigaction sa;

	sa.sa_handler = sig_ack_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);

	i = 0;
	while (*str != '\0')
	{
		c = *str;
		while (i < 8)
		{
			if (c & 0b10000000)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			c = c << 1;
			i++;
			while (!g_ack_received)
				pause();
			g_ack_received = 0;
		}
		i = 0;
		str++;
	}
}

int	main(int argc, char **argv)
{
	int	i;
	int	pid;
	
	pid = ft_atoi(argv[1]);
	if (pid < 1)
		return (2);
	if (argc != 3)
	{
		write (2, "Format: ./client PID String\n", 28);
		return (1);
	}
	send(pid, argv[2]);
	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR1);
		while (!g_ack_received)
			pause();
		g_ack_received = 0;
		i++;
	}
}
