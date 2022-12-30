/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverbonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 20:00:22 by kaboussi          #+#    #+#             */
/*   Updated: 2022/12/30 14:49:46 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	g_lobalpid;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + 48);
}

void	reset(int *c, int *i, int client_pid)
{
	*c = 255;
	*i = 0;
	g_lobalpid = client_pid;
}

void	handler(int sig, siginfo_t *info, void *context)
{
	static int	c = 255;
	static int	i = 0;

	context = NULL;
	if (!g_lobalpid)
		g_lobalpid = info->si_pid;
	if (g_lobalpid != info->si_pid)
		reset(&c, &i, info->si_pid);
	if (sig == SIGUSR1)
		c ^= 128 >> i;
	else if (sig == SIGUSR2)
		c |= 128 >> i;
	i++;
	if (i == 8)
	{
		if (c == 0)
		{
			if (kill (info->si_pid, SIGUSR1) == -1)
				exit(0);
		}
		else
			write(1, &c, 1);
		i = 0;
		c = 255;
	}
}

int	main(void)
{
	struct sigaction	bibo;
	pid_t				pid;

	pid = getpid();
	ft_putnbr(pid);
	write (1, "\n", 1);
	bibo.sa_flags = SA_SIGINFO;
	bibo.sa_sigaction = &handler;
	sigaction(SIGUSR1, &bibo, NULL);
	sigaction(SIGUSR2, &bibo, NULL);
	while (1)
		pause();
}
