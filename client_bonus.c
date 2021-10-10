/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echerell <echerell@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 21:38:30 by echerell          #+#    #+#             */
/*   Updated: 2021/10/10 16:34:29 by echerell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	received(int signum)
{
	(void)signum;
}

void	send_msg(int pid, unsigned char c)
{
	int	bit_shift;

	bit_shift = 8;
	while (bit_shift--)
	{
		if (c & 1 << bit_shift)
		{
			if (kill(pid, SIGUSR1) == -1)
				error(SIGNAL_ERR);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				error(SIGNAL_ERR);
		}
		pause();
		usleep(10);
	}
}

int	main(int argc, char **argv)
{
	int	i;
	int	server_pid;

	if (argc != 3)
		error(FORMAT_ERR);
	i = 0;
	if (!argv[2][0])
		error(EMPTY_ERR);
	server_pid = ft_atoi(argv[1]);
	if (server_pid == 0)
		error(PID_ERR);
	signal(SIGUSR2, received);
	while (argv[2][i])
	{
		send_msg(server_pid, argv[2][i]);
		i++;
	}
	send_msg(server_pid, 0);
	return (0);
}
