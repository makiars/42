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
		write(1, &c, 8);
		write(1, "\n", 1);
	}
}

/*
void	sighandler(int sig)
{
	sig = 0;
	printf("TEST\n");
}
*/

int	main(void)
{
	int	pid;
	struct sigaction sa;

	pid = getpid();
	sa.sa_handler = sighandler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	write(1, ft_itoa(pid), ft_strlen(ft_itoa(pid)));
	while (1)
	{
		pause();
	}
	return (0);
}
