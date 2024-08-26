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

int g_bitcount;

void	sighandler(int signal)
{
	static char	c;

	if (signal == SIGUSR1)
		c = c << 1;
	else if (signal == SIGUSR2)
		c = c << 1 | 0b00000001;

/*	for (int j = 7; j >= 0; j--)
		write(1, (c & (1 << j)) ? "1" : "0", 1);
	write(1, "\n", 1);
*/
	g_bitcount++;
	if (g_bitcount == 8)
	{
		write(1, &c, 1);
		g_bitcount = 0;
		c = 0;
	}
}
/*
#include <stdio.h>
void	sighandler(int sig)
{
	(void) sig;
	sig = 0;
	printf("TEST\n");
}
*/
int	main(void)
{
	char	*pid;
	struct sigaction sa;

	pid = ft_itoa(getpid());
	if (!pid)
		return(1);
	sa.sa_handler = sighandler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	write(1, pid, ft_strlen(pid));
	while(1)
	{
		pause();
	}
	return (0);
}
