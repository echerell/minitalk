/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:25:16 by echerell          #+#    #+#             */
/*   Updated: 2021/10/08 01:07:49 by echerell         ###   ########.fr       */
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

static char	*cat_byte(char *msg, char c)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc((ft_strlen(msg) + 2) * sizeof(char));
	if (!new)
	{
		if (msg)
			free(msg);
		exit(EXIT_FAILURE);
	}
	if (!msg)
	{
		new[0] = c;
		new[1] = '\0';
		return (new);
	}
	while (msg[i])
	{
		new[i] = msg[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = '\0';
	free(msg);
	return (new);
}

static void	take_msg(int signum, siginfo_t *info, void *empty)
{
	static char	*msg;
	static int	bit_shift;
	static int	byte_info;

	(void)empty;
	if (signum == SIGUSR1)
		byte_info |= 1 << (7 - bit_shift);
	if (++bit_shift == 8)
	{
		if (byte_info)
			msg = cat_byte(msg, byte_info);
		else
		{
			ft_putstr_fd(msg, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			free(msg);
			msg = NULL;
			kill(info->si_pid, SIGUSR2);
		}
		bit_shift = 0;
		byte_info = 0;
	}
}

int	main(void)
{
	struct sigaction	act;
	sigset_t			mask;

	ft_bzero(&act, sizeof(act));
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
