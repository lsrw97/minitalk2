/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelisaro <eelisaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:32:06 by eelisaro          #+#    #+#             */
/*   Updated: 2023/04/07 15:07:39 by eelisaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "./ft_printf/libft/libft.h"
#include "./ft_printf/ft_printf.h"

static int	g_character[5];
//g_character[0]	g_character
//g_character[1]	index
//g_character[2]	pid
//g_character[3]	pid status
//g_character[4]	message

void	checksignal(int signal)
{
	if (g_character[1] == 0 && signal)
	{
		if (g_character[3] == 0)
			g_character[3] = 1;
		else if (g_character[3] == 1)
			g_character[3] = 2;
		else
			write(0, &g_character[0], 1);
		g_character[1] = 31;
		g_character[0] = 0;
		if (g_character[3] == 2)
		{
			if (g_character[4] > 0)
				g_character[4]--;
			else
			{
				kill(g_character[2], SIGUSR1);
				g_character[3] = 0;
				g_character[2] = 0;
			}
		}
	}
	else
		g_character[1]--;
}

void	handler1(int signal)
{
	checksignal(signal);
}

void	handler2(int signal)
{
	if (g_character[3] == 0)
		g_character[2] |= 1UL << g_character[1];
	else if (g_character[3] == 1)
		g_character[4] |= 1UL << g_character[1];
	else
		g_character[0] |= 1UL << g_character[1];
	checksignal(signal);
}

int	main(void)
{
	struct sigaction	sa1;
	struct sigaction	sa2;

	g_character[0] = 0;
	g_character[1] = 31;
	g_character[2] = 0;
	g_character[3] = 0;
	g_character[4] = 0;
	sa1.sa_handler = handler1;
	sa2.sa_handler = handler2;
	ft_printf("pid: %d\n", getpid());
	if (sigaction(SIGUSR2, &sa2, NULL) == -1)
	{
		kill(g_character[2], SIGUSR2);
		perror("SIGACTION");
	}
	if (sigaction(SIGUSR1, &sa1, NULL) == -1)
	{
		kill(g_character[2], SIGUSR2);
		perror("SIGACTION");
	}
	while (1)
	{
	}
}
