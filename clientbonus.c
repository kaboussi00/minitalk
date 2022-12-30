/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clientbonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaboussi <kaboussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 20:00:02 by kaboussi          #+#    #+#             */
/*   Updated: 2022/12/30 14:37:38 by kaboussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	n;

	s = 1;
	i = 0;
	n = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			(s *= -1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + str[i] - 48;
		i++;
	}
	return (n * s);
}

void	send0(int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (kill (pid, SIGUSR1) == -1)
			exit(0);
		i++;
		usleep(800);
	}
}

void	sendsig(char *str, int pid)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (j < 8)
		{
			if (str[i] & (128 >> j))
			{
				if (kill(pid, SIGUSR2) == -1)
					exit(0);
			}
			else
			{
				if (kill(pid, SIGUSR1) == -1)
					exit(0);
			}
			j++;
			usleep(800);
		}
		i++;
	}
	send0(pid);
}

void	f(int sig)
{
	(void)sig;
	write(1, "la ballena ciega en el agua la misma cancion!\n", 35);
}

int	main(int ac, char **av)
{
	int	i;
	int	pid;

	i = 0;
	signal(SIGUSR1, f);
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		sendsig(av[2], pid);
	}
	else
		write(1, "you have to give us 2 params!!\n", 31);
	return (0);
}
