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

void	send_bits(char c, int pid)
{
	int	err;

	if (c & 0b10000000)
		err = kill(pid, SIGUSR2);
	else
		err = kill(pid, SIGUSR1);
	if (err)
		exit(1);
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
			send_bits(c, pid);
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
	int	err;

	pid = ft_atoi(argv[1]);
	if (pid < 1)
		return (2);
	if (argc != 3)
	{
		write (1, "Format: ./client PID String\n", 28);
		return (0);
	}
	send(pid, argv[2]);
	i = 0;
	while (i < 8)
	{
		err = kill(pid, SIGUSR1);
		if (err)
			exit (2);
		while (!g_ack_received)
			pause();
		g_ack_received = 0;
		i++;
	}
}
