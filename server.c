/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:25:16 by echerell          #+#    #+#             */
/*   Updated: 2021/10/09 18:59:30 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

static void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	rec;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		rec = (unsigned int)(-1 * n);
	}
	else
		rec = (unsigned int)n;
	if (rec >= 10)
	{
		ft_putnbr_fd(rec / 10, fd);
		ft_putchar_fd(rec % 10 + '0', fd);
	}
	else
		ft_putchar_fd(rec % 10 + '0', fd);
}

static void	take_msg(int signum, siginfo_t *info, void *empty)
{
	static int				bit_shift;
	static unsigned char	byte_info;

	(void)empty;
	if (signum == SIGUSR1)
		byte_info |= 1 << (7 - bit_shift);
	if (++bit_shift == 8)
	{
		if (byte_info)
			ft_putchar_fd(byte_info, STDOUT_FILENO);
		else
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			kill(info->si_pid, SIGUSR2);
		}
		bit_shift = 0;
		byte_info = 0;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	act;
	sigset_t			mask;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Server runs without any arguments\n", STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);
	sigaddset(&mask, SIGUSR2);
	act.sa_sigaction = take_msg;
	act.sa_mask = mask;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	ft_putstr_fd("PID: ", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	while (1)
		pause();
	return (0);
}
