/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 16:44:28 by echerell          #+#    #+#             */
/*   Updated: 2021/10/10 16:49:24 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

static void	take_msg(int signum)
{
	static int				bit_shift;
	static unsigned char	byte_info;

	if (signum == SIGUSR1)
		byte_info |= 1 << (7 - bit_shift);
	if (++bit_shift == 8)
	{
		if (byte_info)
			ft_putchar_fd(byte_info, STDOUT_FILENO);
		else
			ft_putchar_fd('\n', STDOUT_FILENO);
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
		error(SERVER_ERR);
	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);
	sigaddset(&mask, SIGUSR2);
	act.sa_handler = take_msg;
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
